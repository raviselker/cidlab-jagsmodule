rjags::unload.module('Bernoulli')
rjags::load.module('Bernoulli')

Va0 <- runif(1,0,1)
Vb0 <- runif(1,0,1)
a <- runif(1,0,1)
nTrials <- 10

choice <- rbinom(nTrials, 1, 0.5)
correct <- rbinom(nTrials, 1, 0.5)
reward <- as.numeric(choice == correct)
N <- length(reward)

data <- list('choice'=choice, 'reward'=reward)

modelSyntax <- '
model {
    va ~ dunif(0,1)
    vb ~ dunif(0,1)
    a ~ dunif(0,1)

    theta <- reswagner(choice, reward, va, vb, a)
}'

nchains  <- 1      # number of markov chains
nburnin  <- 1000   # number of burnin samples
nsamples <- 1000  # total number of samples
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

