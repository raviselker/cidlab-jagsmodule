SUBDIRS = distributions functions

jagsmod_LTLIBRARIES = Bernoulli.la

Bernoulli_la_SOURCES = Bernoulli.cc

Bernoulli_la_CPPFLAGS = -I$(includedir)/JAGS

Bernoulli_la_LIBADD = distributions/Bernoullidist.la
Bernoulli_la_LIBADD += functions/Bernoullifunc.la
if WINDOWS
Bernoulli_la_LIBADD += -ljags-$(JAGS_MAJOR)
else
Bernoulli_la_LIBADD += -ljags
endif

Bernoulli_la_LDFLAGS = -module -avoid-version
if WINDOWS
Bernoulli_la_LDFLAGS += -no-undefined
endif
