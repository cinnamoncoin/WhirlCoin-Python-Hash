from distutils.core import setup, Extension

whirlpool_hash_module = Extension('whirlpool_hash',
                               sources = ['whirlpoolmodule.c',
                                          'whirlpool.c',
                                          'sphlib/whirlpool.c'],
                               include_dirs=['.', './sphlib'])

setup (name = 'whirlpool_hash',
       version = '1.0',
       description = 'Bindings for whirlpool proof of work used by WhirlCoin',
       ext_modules = [whirlpool_hash_module])
