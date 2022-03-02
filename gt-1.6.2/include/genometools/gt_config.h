#ifndef GT_CONFIG_H
#define GT_CONFIG_H
#define GT_CC "cc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
#define GT_CFLAGS " -g -Wall -Wunused-parameter -pipe -fPIC -Wpointer-arith -Wno-unknown-pragmas -O3 -m32 -m64 -Wno-strict-overflow -Werror"
#define GT_CPPFLAGS "-fno-stack-protector -U_FORTIFY_SOURCE -D_GNU_SOURCE -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DHAVE_MEMMOVE -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN -DLUA_DL_DLOPEN -DLUA_USE_MKSTEMP -DWITHOUT_CAIRO -DGT_THREADS_ENABLED -DSQLITE_THREADSAFE=0 -DHAVE_SQLITE -I/home/vagrant/genometools/src -I/home/vagrant/genometools/obj -I/home/vagrant/genometools/src/external/zlib-1.2.8 -I/home/vagrant/genometools/src/external/md5-1.2/src -I/home/vagrant/genometools/src/external/lua-5.1.5/src -I/home/vagrant/genometools/src/external/luafilesystem-1.5.0/src -I/home/vagrant/genometools/src/external/lpeg-0.10.2 -I/home/vagrant/genometools/src/external/expat-2.0.1/lib -I/home/vagrant/genometools/src/external/bzip2-1.0.6 -I/home/vagrant/genometools/src/external/samtools-0.1.18 -I/home/vagrant/genometools/src/external/sqlite-3.33.0 -I/home/vagrant/genometools/src/external/tre/include -I/home/vagrant/genometools/src/external/sqlite-3.33.0"
#define GT_VERSION "1.6.2"
#define GT_MAJOR_VERSION 1
#define GT_MINOR_VERSION 6
#define GT_MICRO_VERSION 2
#endif
