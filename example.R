rjags::unload.module('Bernoulli')
rjags::load.module('Bernoulli')

Va0 <- runif(1,0,1)
Vb0 <- runif(1,0,1)
a <- runif(1,0,1)
nTrials <- 2

choice <- rbinom(nTrials, 1, 0.5)
correct <- rbinom(nTrials, 1, 0.5)
reward <- as.numeric(choice == correct)

data <- list('choice'=choice, 'reward'=reward, 'va'=Va0, 'vb'=Vb0 , 'a'=a)

model <- '
model {
    p <- logbern(choice, reward, va, vb, a)
}'

model <- rjags::jags.model(file = textConnection(model),
                           data = data,
                           n.chains = 4,
                           n.adapt = 100)

