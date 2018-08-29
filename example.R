rjags::unload.module('cidlab')
rjags::load.module('cidlab')

Va0 <- runif(1, 0, 1)
Vb0 <- runif(1, 0, 1)
a <- runif(1,0,1)
nTrials <- 100

choice <- rbinom(1, 1, 0.5)
correct <- c(rbinom(nTrials / 2, 1, 0.9), rbinom(nTrials / 2, 1, 0.3))

Va <- Va0; Vb <- Vb0; theta <- numeric(nTrials); reward <- numeric(nTrials)
for (i in 1:nTrials) {

    c <- choice[i]
    r <- as.numeric(choice[i] == correct[i])
    reward[i] <- r

    if (c == 0)
        Va <- Va + a*(r - Va)
    else
        Vb <- Vb + a*(r - Vb)

    theta[i] <- exp(Vb) / (exp(Va) + exp(Vb))
    choice[i+1] <- rbinom(1, 1, theta[i])
}

data <- list('N'=nTrials, 'choice'=choice, 'choice2'=choice, 'reward'=reward)

modelSyntax <- '
model {
    va ~ dunif(0,1)
    vb ~ dunif(0,1)
    a ~ dunif(0,1)

    theta <- reswagner(choice, reward, va, vb, a)
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
    inits[[i]] <- list(va=va, vb=vb, a=a)
}


model <- rjags::jags.model(file = textConnection(modelSyntax),
                           data = data,
                           n.chains = nchains, inits = inits)

update(model, nburnin)
samples <- rjags::jags.samples(model, c('a'), nsamples, thin=nthin)

plot(density(samples[[1]][,,]))
