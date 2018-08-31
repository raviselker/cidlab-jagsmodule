resWagnerSim <- function(N, a = NULL, beta = NULL, pcor = 0.5, seed = NULL) {
    
    if ( ! is.null(seed))
        set.seed(seed)
    
    Va0 <- runif(1, 0, 1)
    Vb0 <- runif(1, 0, 1)
    
    if (is.null(a))
        a <- runif(1, 0, 1)
    
    if (is.null(beta))
        beta <- rgamma(1, 2, 1)

    choice <- rbinom(1, 1, 0.5)
    correct <- rbinom(N, 1, pcor)
    
    Va <- Va0; Vb <- Vb0; theta <- numeric(N); reward <- numeric(N)
    for (i in 1:N) {
        
        c <- choice[i]
        r <- as.numeric(choice[i] == correct[i])
        reward[i] <- r
        
        if (c == 0)
            Va <- Va + a*(r - Va)
        else
            Vb <- Vb + a*(r - Vb)
        
        theta[i] <- exp(beta * (Vb - Va)) / (1 + exp(beta * (Vb - Va)))
        choice[i+1] <- rbinom(1, 1, theta[i])
    }
    
    data <- list('N'=N, 'theta'=theta, 'a'=a, 'beta'=beta, 'choice'=choice, 'correct'=correct, 'reward'=reward)
    
    return(data)
}