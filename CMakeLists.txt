cmake_minimum_required(VERSION 3.1)

project(tippecanoe)

#add_definitions(-DUNICODE)

add_library(asprintf STATIC
    win32/asprintf/asprintf.c
    win32/asprintf/asprintf.h
    win32/asprintf/vasprintf-msvc.c
)

target_include_directories(asprintf
    INTERFACE win32/asprintf
)

add_library(dirent INTERFACE)

target_include_directories(dirent
    INTERFACE win32/dirent/include
)

add_library(getopt STATIC
    win32/getopt_port/getopt.c
    win32/getopt_port/getopt.h
)

target_include_directories(getopt
    INTERFACE win32/getopt_port
)

add_library(mman STATIC
    win32/mman-win32/mman.c
    win32/mman-win32/mman.h
)

target_include_directories(mman
    INTERFACE win32/mman-win32
)

add_library(pthreads STATIC
    win32/pthreads4w/pthread.c
)
set_source_files_properties(win32/pthreads4w/pthread.c PROPERTIES LANGUAGE CXX)

target_include_directories(pthreads
    PUBLIC win32/pthreads4w
)

target_compile_definitions(pthreads
	PRIVATE -D__PTW32_CLEANUP_CXX -DHAVE_CONFIG_H=1 -DPTW32_BUILD_INLINED -D__PTW32_STATIC_LIB
	PUBLIC -D__PTW32_STATIC_LIB
)

target_link_libraries(pthreads
	PRIVATE Ws2_32.lib
)

add_library(sqlite STATIC
    win32/sqlite/sqlite3.c
    win32/sqlite/sqlite3.h
)

target_include_directories(sqlite
    INTERFACE win32/sqlite
)

add_library(zlib STATIC
	win32/zlib/zconf.h
	win32/zlib/zlib.h
    win32/zlib/crc32.h
    win32/zlib/deflate.h
    win32/zlib/gzguts.h
    win32/zlib/inffast.h
    win32/zlib/inffixed.h
    win32/zlib/inflate.h
    win32/zlib/inftrees.h
    win32/zlib/trees.h
    win32/zlib/zutil.h
    win32/zlib/adler32.c
    win32/zlib/compress.c
    win32/zlib/crc32.c
    win32/zlib/deflate.c
    win32/zlib/gzclose.c
    win32/zlib/gzlib.c
    win32/zlib/gzread.c
    win32/zlib/gzwrite.c
    win32/zlib/inflate.c
    win32/zlib/infback.c
    win32/zlib/inftrees.c
    win32/zlib/inffast.c
    win32/zlib/trees.c
    win32/zlib/uncompr.c
    win32/zlib/zutil.c
)

target_include_directories(zlib
    INTERFACE win32/zlib
)

set(tippecanoe_HDRS
	catch/catch.hpp
	jsonpull/jsonpull.h
	milo/dtoa_milo.h
	protozero/byteswap.hpp
	protozero/config.hpp
	protozero/exception.hpp
	protozero/iterators.hpp
	protozero/pbf_builder.hpp
	protozero/pbf_message.hpp
	protozero/pbf_reader.hpp
	protozero/pbf_writer.hpp
	protozero/types.hpp
	protozero/varint.hpp
	protozero/version.hpp
    csv.hpp
    dirtiles.hpp
    evaluator.hpp
    geobuf.hpp
    geocsv.hpp
    geojson-loop.hpp
    geojson.hpp
    geometry.hpp
    main.hpp
    mbtiles.hpp
    memfile.hpp
    mvt.hpp
    options.hpp
    plugin.hpp
    pool.hpp
    projection.hpp
    read_json.hpp
    serial.hpp
    text.hpp
    tile.hpp
    version.hpp
    write_json.hpp
)

set(tippecanoe_SRCS
	jsonpull/jsonpull.c
    csv.cpp
    dirtiles.cpp
    evaluator.cpp
    geobuf.cpp
    geocsv.cpp
    geojson-loop.cpp
    geojson.cpp
    geometry.cpp
    main.cpp
    mbtiles.cpp
    memfile.cpp
    mvt.cpp
    plugin.cpp
    pool.cpp
    projection.cpp
    read_json.cpp
    serial.cpp
    text.cpp
    tile.cpp
    write_json.cpp
)

add_executable(tippecanoe ${tippecanoe_HDRS} ${tippecanoe_SRCS})

target_compile_definitions(tippecanoe PRIVATE -DTIPPEWIN32)

target_include_directories(tippecanoe PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tippecanoe
    asprintf
    dirent
    getopt
    mman
    pthreads
	sqlite
	zlib
)

