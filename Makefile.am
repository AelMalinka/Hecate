ACLOCAL_AMFLAGS = -I m4
#2013-10-11 AMR XXX: non-portable assignment
AM_CXXFLAGS := -I$(srcdir)/src -I$(srcdir)/external/pcg-cpp/include $(AM_CXXFLAGS)

mainheadersdir = $(includedir)/Entropy/Hecate
mainheaders_HEADERS = \
	src/Exception.hh \
	src/Character.hh \
	src/Character.impl.hh \
	src/Stat.hh \
	src/Stat.impl.hh \
	src/Skill.hh \
	src/Skill.impl.hh \
	src/Random.hh \
	src/Check.hh \
	src/Check.impl.hh \
	src/Modifier.hh \
	src/Modifier.impl.hh

mainheaders_HEADERS += \
	external/pcg-cpp/include/pcg_random.hpp

lib_LTLIBRARIES = libhecate.la

libhecate_la_SOURCES = \
	src/Random.cc \
	src/Modifier.cc \
	src/Check.cc

check_PROGRAMS = 

if GTEST
check_PROGRAMS += \
	character-stat \
	character-skill \
	character-character \
	random-pcg \
	random-base \
	check-modifier \
	check-check

# 2013-09-30 AMR TODO: abstract some of this logic to autogeneration
testLDADD = -lgtest_main -lgtest -lhecate $(AM_LDADD)
testLDFLAGS = -pthread $(AM_LDFLAGS)

character_character_SOURCES = test/character/character.cc
character_character_LDADD = $(testLDADD)
character_character_LDFLAGS = $(testLDFLAGS)

character_stat_SOURCES = test/character/character-stat.cc
character_stat_LDADD = $(testLDADD)
character_stat_LDFLAGS = $(testLDFLAGS)

character_skill_SOURCES = test/character/character-skill.cc
character_skill_LDADD = $(testLDADD)
character_skill_LDFLAGS = $(testLDFLAGS)

random_pcg_SOURCES = test/random/pcg.cc
random_pcg_LDADD = $(testLDADD)
random_pcg_LDFLAGS = $(testLDFLAGS)

random_base_SOURCES = test/random/base.cc
random_base_LDADD = $(testLDADD)
random_base_LDFLAGS = $(testLDFLAGS)

check_modifier_SOURCES = test/check/modifier.cc
check_modifier_LDADD = $(testLDADD)
check_modifier_LDFLAGS = $(testLDFLAGS)

check_check_SOURCES = test/check/check.cc
check_check_LDADD = $(testLDADD)
check_check_LDFLAGS = $(testLDFLAGS)
endif

TESTSUITE = $(srcdir)/test/testsuite
TESTSUITE_FILES = \
	$(srcdir)/test/character.at \
	$(srcdir)/test/random.at \
	$(srcdir)/test/check.at

EXTRA_DIST = \
	$(TESTSUITE_FILES) \
	$(srcdir)/test/testsuite.at \
	$(srcdir)/package.m4 \
	$(TESTSUITE) \
	$(srcdir)/test/atlocal.in

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:; {\
		echo '# Signature of the current package. (auto-generated)' && \
		echo 'm4_define([AT_PACKAGE_NAME],' && \
		echo '  [$(PACKAGE_NAME)])' && \
		echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		echo '  [$(PACKAGE_TARNAME)])' && \
		echo 'm4_define([AT_PACKAGE_VERSION],' && \
		echo '  [$(PACKAGE_VERSION)])' && \
		echo 'm4_define([AT_PACKAGE_STRING],' && \
		echo '  [$(PACKAGE_STRING)])' && \
		echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		echo '  [$(PACKAGE_BUGREPORT)])'; \
		echo 'm4_define([AT_PACKAGE_URL],' && \
		echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

#2013-10-11 AMR XXX: $(shell x) is a GNUMake extension
check-local: test/atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(shell pwd)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
