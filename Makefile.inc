mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	Controller.o \
	Walker.o \
	LineTracer.o \
	Mileage.o \
	Tracer.o \
	Scenario.o \
	ScenarioTracer.o \
	ScenarioTracerWithLineCnt.o \
	RandomWalker.o \
	LineMonitor.o \
	Starter.o \
	Pid.o \
	DifficultScenarioTracer.o \
	SimpleTimer.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

INCLUDES += -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common

endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit

COPTS += -std=gnu++11