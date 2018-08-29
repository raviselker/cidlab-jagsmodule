SUBDIRS = distributions functions

jagsmod_LTLIBRARIES = cidlab.la

cidlab_la_SOURCES = cidlab.cc

cidlab_la_CPPFLAGS = -I$(includedir)/JAGS

cidlab_la_LIBADD = distributions/Bernoullidist.la
cidlab_la_LIBADD += functions/cidlabfunc.la
if WINDOWS
cidlab_la_LIBADD += -ljags-$(JAGS_MAJOR)
else
cidlab_la_LIBADD += -ljags
endif

cidlab_la_LDFLAGS = -module -avoid-version
if WINDOWS
cidlab_la_LDFLAGS += -no-undefined
endif
