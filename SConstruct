#            tastes like -*- python -*-

# Copyright 2007 Hewlett-Packard Development Company, L.P.
# HP Confidential.  No photocopying.  SCons rocks.

# Author: Tim Potter <tpot@hp.com>

import os

# CmpiCpp library

my_env = Environment()

prefix = ARGUMENTS.get('PREFIX', '/usr/local')

my_env.Append(CCFLAGS = '-g -W -Wall -Wno-multichar -Werror',
              CPPPATH = ['#CMPI'],
              ENV = {'HOME': os.environ['HOME']},
              PREFIX = prefix)

libCmpiCpp_source = [
    'CmpiName.cpp',
    'CmpiStatus.cpp',
    'CmpiData.cpp',
    'CmpiObjectPath.cpp',
    'CmpiInstance.cpp',
    'CmpiResult.cpp',
    'CmpiContext.cpp',
    'CmpiArray.cpp',
    'CmpiArgs.cpp',
    'CmpiEnumeration.cpp',
    'CmpiDateTime.cpp',
    'CmpiBroker.cpp',
    'CmpiProvider.cpp',
    'CmpiInstanceProvider.cpp',
    'CmpiAssociationProvider.cpp',
    'CmpiMethodProvider.cpp',
    'CmpiIndicationProvider.cpp',
]

libCmpiCpp = my_env.SharedLibrary(
    'libCmpiCpp',
    source = libCmpiCpp_source)

libCmpiCpp_headers = [
    'CmpiCpp.h',
    'CmpiStatus.h',
    'CmpiName.h',
    'CmpiArray.h',
    'CmpiData.h',
    'CmpiObjectPath.h',
    'CmpiInstance.h',
    'CmpiResult.h',
    'CmpiContext.h',
    'CmpiArgs.h',
    'CmpiEnumeration.h',
    'CmpiDateTime.h',
    'CmpiBroker.h',
    'CmpiProvider.h',
    'CmpiInstanceProvider.h',
    'CmpiAssociationProvider.h',
    'CmpiMethodProvider.h',
    'CmpiIndicationProvider.h',
]

libCmpiCpp_CMPI_headers = [
    'CMPI/cmpi_cql.h',
    'CMPI/cmpidt.h',
    'CMPI/cmpift.h',
    'CMPI/cmpimacs.h',
    'CMPI/cmpios.h',
    'CMPI/cmpipl.h',
]

# CmpiCppBroker library

libCmpiCppBroker_source = [
    'CmpiBrokerBroker.cpp',
    'CmpiBrokerArray.cpp',
    'CmpiBrokerInstance.cpp',
    'CmpiBrokerObjectPath.cpp',
    'CmpiBrokerResult.cpp',
    'CmpiBrokerString.cpp',
    'CmpiBrokerEnumeration.cpp',
    'CmpiBrokerContext.cpp',
    'CmpiBrokerDateTime.cpp',
    'UnimplementedFT.cpp',
]

libCmpiCppBroker = my_env.SharedLibrary(
    'libCmpiCppBroker',
    source = libCmpiCppBroker_source)

libCmpiCppBroker_headers = [
    'CmpiCppBroker.h',
    'CmpiBrokerBroker.h',
    'CmpiBrokerArray.h',
    'CmpiBrokerInstance.h',
    'CmpiBrokerObjectPath.h',
    'CmpiBrokerResult.h',
    'CmpiBrokerString.h',
    'CmpiBrokerEnumeration.h',
    'CmpiBrokerContext.h',
    'CmpiBrokerDateTime.h',
    'UnimplementedFT.h',
]

# Install

my_env.Alias('install',
             my_env.Install('$PREFIX/lib', [libCmpiCpp, libCmpiCppBroker]))


my_env.Alias('install',
             my_env.Install('$PREFIX/include/cmpicpp', 
                            [libCmpiCpp_headers, libCmpiCppBroker_headers]))

my_env.Alias('install',
             my_env.Install('$PREFIX/include/cmpicpp/CMPI',
                            libCmpiCpp_CMPI_headers))
