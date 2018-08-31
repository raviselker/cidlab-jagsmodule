rjags::unload.module('cidlab')
rjags::load.module('cidlab')

source('simData.R')

dataAll <- resWagnerSim(1000, a=0.4, beta=5, pcor=0.7)
plot(dataAll$theta, type='l')

data <- list(N=dataAll$N, choice=dataAll$choice, choice2=dataAll$choice, reward=dataAll$reward)

#### Using the JAGS module ----

modelSyntax <- '
model {
    va ~ dunif(0,1)
    vb ~ dunif(0,1)
    a ~ dunif(0,1)
    beta ~ dgamma(2,1)

    theta <- reswagner(choice, reward, va, vb, a, beta)
    for (i in 1:N) {
        choice2[i] ~ dbern(theta[i])
    }
}'

nchains  <- 1      # number of markov chains
nburnin  <- 1000   # number of burnin samples
nsamples <- 10000  # total number of samples
nthin    <- 1      # thinning per chain

# Set initial values
inits <- list()
for (i in 1:nchains) {
    va <- runif(1, 0, 1)
    vb <- runif(1, 0, 1)
    a <- runif(1, 0, 1)
    beta <- rgamma(1, 2, 1)
    inits[[i]] <- list(va=va, vb=vb, a=a)
}


model <- rjags::jags.model(file = textConnection(modelSyntax),
                           data = data,
                           n.chains = nchains, inits = inits)

update(model, nburnin)
samples <- rjags::jags.samples(model, c('theta','a', 'beta'), nsamples, thin=nthin)

plot(density(samples[['a']][,,]))
plot(samples[['a']][,,], samples[['beta']][,,])

#### Using straight JAGS code ----

modelSyntax2 <- '
model {
    a ~ dunif(0,1)
    va ~ dunif(0,1)
    vb ~ dunif(0,1)
    beta ~ dgamma(2,1)

    Va[1] <- va
    Vb[1] <- vb
    theta[1] <- exp(Va[1]) / (exp(Va[1]) + exp(Vb[1]))
    choice[1] ~ dbern(theta[1])

    for (i in 2:N) {
        Va[i] <- ifelse(choice[i-1] == 0,  Va[i-1] + a*(reward[i-1] - Va[i-1]), Va[i-1])
        Vb[i] <- ifelse(choice[i-1] == 1,  Vb[i-1] + a*(reward[i-1] - Vb[i-1]), Vb[i-1])
        theta[i] <- exp(beta * (Vb[i] - Va[i])) / (1 + exp(beta * (Vb[i] - Va[i])))
        choice[i] ~ dbern(theta[i])
    }
}'

data2 <- list('choice'=dataAll$choice, 'reward'=dataAll$reward, 'N'=dataAll$N)

model2 <- rjags::jags.model(file = textConnection(modelSyntax2),
                           data = data2,
                           n.chains = nchains, inits = inits)

update(model2, nburnin)

samples2 <- rjags::jags.samples(model2, c('beta','a'), nsamples, thin=nthin)

plot(density(samples2[['a']][,,]))
