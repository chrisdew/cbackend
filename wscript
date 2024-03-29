import os
import Options

srcdir = '.'
blddir = 'build'
VERSION = '0.3.0'

def set_options(opt):
  opt.tool_options('compiler_cxx')
  opt.tool_options('compiler_cc')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('compiler_cc')
  conf.check_tool('node_addon')

  conf.env.append_value('CCFLAGS', ['-O3', '-std=gnu99', '-fPIC'])
  conf.env.append_value('CXXFLAGS', ['-O3'])
  if Options.platform == 'darwin': conf.env.append_value('LINKFLAGS', ['-undefined', 'dynamic_lookup'])

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'cbackend'
  obj.source = 'cbackend.cc data.c'
  obj.uselib = ['NODE']

