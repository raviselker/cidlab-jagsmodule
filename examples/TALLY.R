#### Prepare the data ----

library('tidyverse')

dataPre <- read.csv("data/LessIsMoreData.csv") %>% 
    filter(country == 1, recogA == 1, recogB == 1) %>%  # German cities that were recognized
    select(-country, -recogA, -recogB) %>%              # Remove unnecessary columns
    mutate(decision = abs(decision - 2))                # Recode decision (1 = A, 0 = B)

stimA <- dataPre$stimA
stimB <- dataPre$stimB
dec <- dataPre$decision

nTrials <- nrow(dataPre)

coding <- R.matlab::readMat('data/FeatureEnvironments.mat')$d[,,1]
val <- as.numeric(coding$validity)
cues <- coding$cues

data <- list(dec=dec, stimA=stimA, stimB=stimB, 
             val=val, cues=cues, nTrials=nTrials)


#### Define the model ----

modelSyntax <- '
model {
    for (i in 1:nTrials) {
        out[i,1:2] <- TALLY(cues[stimA[i],], cues[stimB[i],], s)
        choice[i] <- out[i,1]
        ev[i] <- out[i,2]
        dec[i] ~ dbern(equals(choice[i],1)*(1-gamma) + equals(choice[i],0)*gamma + equals(choice[i], 0.5)*0.5)
    }

    s <- order(-val)
    gamma ~ dunif(0, 0.5)
}'


#### Fit the model ----

nchains  <- 1      # number of markov chains
nburnin  <- 1000   # number of burnin samples
nsamples <- 10000  # total number of samples
nthin    <- 1      # thinning per chain

rjags::load.module('wfComboPack')


model <- rjags::jags.model(file = textConnection(modelSyntax),
                           data = data,
                           n.chains = nchains)

update(model, nburnin)
samples <- rjags::jags.samples(model, c('gamma', 'choice'), nsamples, thin=nthin)


#### Check results ----

# plot(density(samples[['gamma']]))
