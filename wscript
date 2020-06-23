#!/usr/bin/env waf
VERSION='0.0.0'
APPNAME='cogs'

import os.path as osp

def options(opt):
    opt.load('compiler_cxx')
    opt.load('waf_unit_test')
    opt.add_option('--quell-tests', action='store_true', default=False,
                   help='Compile but do not run the tests (default=%default)')
    opt.add_option('--with-ers', default=None,
                   help='Set to ERS install area')
    opt.add_option('--with-nljs', default=None,
                   help='Point nlohmann json install area')
    opt.recurse("demo")

def configure(cfg):
    cfg.load('compiler_cxx')
    cfg.load('waf_unit_test')
    cfg.env.CXXFLAGS += ['-std=c++17', '-ggdb3', '-Wall',
                         '-Wpedantic', '-Werror']
    nljs = getattr(cfg.options, 'with_nljs', None)
    if nljs:
        print("using " + nljs)
        setattr(cfg.env, 'INCLUDES_NLJS', [osp.join(nljs, "include")])

    cfg.check(features='cxx cxxprogram', define_name='HAVE_NLJS',
              header_name='nlohmann/json.hpp', 
              use='NLJS', uselib_store='NLJS', mandatory=True)

    ers = getattr(cfg.options, 'with_ers',None)
    if ers:
        setattr(cfg.env, 'RPATH_ERS', [osp.join(ers, 'lib')]);
        setattr(cfg.env, 'LIBPATH_ERS', [osp.join(ers, 'lib')]);
        setattr(cfg.env, 'INCLUDES_ERS', [osp.join(ers, 'include')]);

    cfg.check(features='cxx cxxprogram', define_name='HAVE_ERS',
              header='ers/ers.h', lib=['ers','ErsBaseStreams'],
              use='ERS', uselib_store='ERS', mandatory=True)

    cfg.write_config_header('config.hpp')
    cfg.recurse("demo")
    #print (cfg.env)

def build(bld):
    bld.recurse("test")
    
    sources = bld.path.ant_glob('src/*.cpp');
    bld.shlib(features='cxx', includes='inc', 
              source = sources, target='cogs',
              uselib_store='COGS', use=['ERS','NLJS'])
    
    bld.install_files('${PREFIX}/include/cogs',
                      bld.path.ant_glob("inc/cogs/**/*.hpp"),
                      cwd=bld.path.find_dir('inc/cogs'),
                      relative_trick=True)                      

    from waflib.Tools import waf_unit_test
    bld.add_post_fun(waf_unit_test.summary)
    bld.recurse("demo")
