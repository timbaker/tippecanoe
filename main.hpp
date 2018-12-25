#ifndef MAIN_HPP
#define MAIN_HPP

#include <stddef.h>
#include <atomic>
#include <string>

#if defined(TIPPEWIN32)
// FIXME: the comment below says 'struct index' should be 32 bytes, but it's 36 even with 'pragma pack(1)'.
// It must align with virtual memory allocation granularity (a multiple of 1024).
struct index {
    long long start = 0;
    long long end = 0;
    unsigned long long ix = 0;
    unsigned long long seq;
    short segment = 0;
    unsigned short t;
    uint8_t pad[64 - 36]; // pad to 64 bytes;

    index()
        : seq(0),
          t(0) {
    }
};

static_assert (sizeof(index) == 64, "struct index must align to virtual-memory allocation granularity");

#else

struct index {
	long long start = 0;
	long long end = 0;
	unsigned long long ix = 0;
	short segment = 0;
	unsigned short t : 2;
	unsigned long long seq : (64 - 18);  // pack with segment and t to stay in 32 bytes

	index()
	    : t(0),
	      seq(0) {
	}
};

#endif

struct clipbbox {
	double lon1;
	double lat1;
	double lon2;
	double lat2;

	long long minx;
	long long miny;
	long long maxx;
	long long maxy;
};

extern std::vector<clipbbox> clipbboxes;

void checkdisk(std::vector<struct reader> *r);

extern int geometry_scale;
extern int quiet;
extern int quiet_progress;
extern double progress_interval;
extern std::atomic<double> last_progress;

extern size_t CPUS;
extern size_t TEMP_FILES;

extern size_t max_tile_size;
extern size_t max_tile_features;
extern int cluster_distance;
extern std::string attribute_for_id;

int mkstemp_cloexec(char *name);
#if defined(TIPPEWIN32)
#define O_CLOEXEC 0
#endif
FILE *fopen_oflag(const char *name, const char *mode, int oflag);
bool progress_time();

#define MAX_ZOOM 24

#endif
