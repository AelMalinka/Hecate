ACLOCAL_AMFLAGS = -I m4
#2013-10-11 AMR XXX: non-portable assignment
AM_CPPFLAGS = -I$(srcdir)/src -I$(srcdir)/external/pcg-cpp/include

mainheadersdir = $(includedir)/Entropy/Hecate
mainheaders_HEADERS = \
	src/Exception.hh \
	src/Percent.hh \
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
	src/Modifier.impl.hh \
	src/Event.hh \
	src/Trait.hh \
	src/Trait.impl.hh \
	src/Template.hh \
	src/Template.impl.hh \
	src/ModifierType.hh \
	src/ModifierList.hh \
	src/Resource.hh \
	src/Resource.impl.hh

algorithmsdir = $(includedir)/Entropy/Hecate/Algorithms
algorithms_HEADERS = \
	src/Algorithms/Linear.hh \
	src/Algorithms/Linear.impl.hh

lib_LTLIBRARIES = libhecate.la

libhecate_la_SOURCES = \
	src/Random.cc \
	src/Modifier.cc \
	src/Check.cc \
	src/Event.cc \
	src/Percent.cc \
	src/ModifierType.cc \
	src/ModifierList.cc

check_PROGRAMS = 

if GTEST
check_PROGRAMS += \
	character-stat \
	character-skill \
	character-character \
	character-resource \
	random-pcg \
	random-base \
	check-check \
	trait-event \
	trait-trait \
	template-template \
	modifier-type \
	modifier-modifier \
	modifier-list

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

character_resource_SOURCES = test/character/resource.cc
character_resource_LDADD = $(testLDADD)
character_resource_LDFLAGS = $(testLDFLAGS)

random_pcg_SOURCES = test/random/pcg.cc
random_pcg_LDADD = $(testLDADD)
random_pcg_LDFLAGS = $(testLDFLAGS)

random_base_SOURCES = test/random/base.cc
random_base_LDADD = $(testLDADD)
random_base_LDFLAGS = $(testLDFLAGS)

check_check_SOURCES = test/check/check.cc
check_check_LDADD = $(testLDADD)
check_check_LDFLAGS = $(testLDFLAGS)

trait_event_SOURCES = test/trait/event.cc
trait_event_LDADD = $(testLDADD)
trait_event_LDFLAGS = $(testLDFLAGS)

trait_trait_SOURCES = test/trait/trait.cc
trait_trait_LDADD = $(testLDADD)
trait_trait_LDFLAGS = $(testLDFLAGS)

template_template_SOURCES = test/template/template.cc
template_template_LDADD = $(testLDADD)
template_template_LDFLAGS = $(testLDFLAGS)

modifier_modifier_SOURCES = test/modifier/modifier.cc
modifier_modifier_LDADD = $(testLDADD)
modifier_modifier_LDFLAGS = $(testLDFLAGS)

modifier_type_SOURCES = test/modifier/type.cc
modifier_type_LDADD = $(testLDADD)
modifier_type_LDFLAGS = $(testLDFLAGS)

modifier_list_SOURCES = test/modifier/list.cc
modifier_list_LDADD = $(testLDADD)
modifier_list_LDFLAGS = $(testLDFLAGS)
endif

TESTSUITE = $(srcdir)/test/testsuite
TESTSUITE_FILES = \
	$(srcdir)/test/character.at \
	$(srcdir)/test/random.at \
	$(srcdir)/test/check.at \
	$(srcdir)/test/trait.at \
	$(srcdir)/test/template.at \
	$(srcdir)/test/modifier.at

EXTRA_DIST = \
	$(srcdir)/external/pcg-cpp/include/pcg_extras.hpp \
	$(srcdir)/external/pcg-cpp/include/pcg_random.hpp \
	$(srcdir)/external/pcg-cpp/include/pcg_uint128.hpp \
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
