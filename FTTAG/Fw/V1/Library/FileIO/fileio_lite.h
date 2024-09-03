#ifndef FILEIO_LITE_H
#define FILEIO_LITE_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "fileio_lite_cfg.h"
#endif

// Macro for file IO and MSD
#ifndef FILEIO_DISK_NAME
#define FILEIO_DISK_NAME                "BOOTLOADER " // Volume Label is exactly 11 bytes
#endif

#ifndef FILEIO_DISK_NAME_IN_BYTE
#define FILEIO_DISK_NAME_IN_BYTE        'B', 'O', 'O', 'T', 'L', 'O', 'A', 'D', 'E', 'R', ' '
#endif

#ifndef FILEIO_CONFIG_MAX_DRIVES
// Macro indicating how many drives can be mounted simultaneously.
#define FILEIO_CONFIG_MAX_DRIVES        1
#endif

#ifndef FILEIO_CONFIG_DELIMITER
// Delimiter for directories.
#define FILEIO_CONFIG_DELIMITER         '/'
#endif

#ifndef FILEIO_CONFIG_MEDIA_SECTOR_SIZE
// Macro defining the maximum supported sector size for the FILEIO module.  This value should always be 512 , 1024, 2048, or 4096 bytes.
// Most media uses 512-byte sector sizes.
#define FILEIO_CONFIG_MEDIA_SECTOR_SIZE 512
#endif

#ifndef FILEIO_CONFIG_SEARCH_DISABLE
// Uncomment FILEIO_CONFIG_FUNCTION_SEARCH to disable the functions used to search for files.
#define FILEIO_CONFIG_SEARCH_DISABLE
#endif

#ifndef FILEIO_CONFIG_FORMAT_DISABLE
// Uncomment FILEIO_CONFIG_FUNCTION_FORMAT to disable the function used to format drives.
#define FILEIO_CONFIG_FORMAT_DISABLE
#endif

#ifndef FILEIO_CONFIG_DIRECTORY_DISABLE
// Uncomment FILEIO_CONFIG_FUNCTION_DIRECTORY to disable use of directories on your drive.  Disabling this feature will
// limit you to performing all file operations in the root directory.
#endif

#ifndef FILEIO_CONFIG_DIRECTORY_DISABLE
//#define FILEIO_CONFIG_DIRECTORY_DISABLE
#endif

#ifndef FILEIO_CONFIG_PROGRAM_MEMORY_STRINGS_DISABLE
// Uncomment FILEIO_CONFIG_FUNCTION_PROGRAM_MEMORY_STRINGS to disable functions that accept ROM string arguments.
// This is only necessary on PIC18 parts.
#define FILEIO_CONFIG_PROGRAM_MEMORY_STRINGS_DISABLE
#endif

#ifndef FILEIO_INVALID_HANDLE
#define FILEIO_INVALID_HANDLE                       NULL
#endif

#ifndef FILEIO_FILE_NAME_LENGTH_8P3
#define FILEIO_FILE_NAME_LENGTH_8P3                 12 // Maximum file name length for 8.3 formatted files
#endif

#ifndef FILEIO_FILE_NAME_LENGTH_8P3_NO_RADIX
#define FILEIO_FILE_NAME_LENGTH_8P3_NO_RADIX        11 // Maximum file name length for 8.3 formatted files with no radix
#endif

typedef enum {
    FILEIO_RESULT_SUCCESS = 0, // File operation was a success
    FILEIO_RESULT_FAILURE = -1 // File operation failed
} FILEIO_RESULT;

typedef enum {
    FILEIO_FORMAT_ERASE = 0, // Erases the contents of the partition
    FILEIO_FORMAT_BOOT_SECTOR // Creates a boot sector based on user-specified information and erases any existing information
} FILEIO_FORMAT_MODE;

typedef enum {
    FILEIO_ERROR_NONE = 0, // No error
    FILEIO_ERROR_ERASE_FAIL, // An erase failed
    FILEIO_ERROR_NOT_PRESENT, // No device was present
    FILEIO_ERROR_NOT_FORMATTED, // The disk is of an unsupported format
    FILEIO_ERROR_BAD_PARTITION, // The boot record is bad
    FILEIO_ERROR_UNSUPPORTED_FS, // The file system type is unsupported
    FILEIO_ERROR_INIT_ERROR, // An initialization error has occured
    FILEIO_ERROR_UNINITIALIZED, // An operation was performed on an uninitialized device
    FILEIO_ERROR_BAD_SECTOR_READ, // A bad read of a sector occured
    FILEIO_ERROR_WRITE, // Could not write to a sector
    FILEIO_ERROR_INVALID_CLUSTER, // Invalid cluster value > maxcls
    FILEIO_ERROR_DRIVE_NOT_FOUND, // The specified drive could not be found
    FILEIO_ERROR_FILE_NOT_FOUND, // Could not find the file on the device
    FILEIO_ERROR_DIR_NOT_FOUND, // Could not find the directory
    FILEIO_ERROR_BAD_FILE, // File is corrupted
    FILEIO_ERROR_DONE, // No more files in this directory
    FILEIO_ERROR_COULD_NOT_GET_CLUSTER, // Could not load/allocate next cluster in file
    FILEIO_ERROR_FILENAME_TOO_LONG, // A specified file name is too long to use
    FILEIO_ERROR_FILENAME_EXISTS, // A specified filename already exists on the device
    FILEIO_ERROR_INVALID_FILENAME, // Invalid file name
    FILEIO_ERROR_DELETE_DIR, // The user tried to delete a directory with FILEIO_Remove
    FILEIO_ERROR_DELETE_FILE, // The user tried to delete a file with FILEIO_DirectoryRemove
    FILEIO_ERROR_DIR_FULL, // All root dir entry are taken
    FILEIO_ERROR_DRIVE_FULL, // All clusters in partition are taken
    FILEIO_ERROR_DIR_NOT_EMPTY, // This directory is not empty yet, remove files before deleting
    FILEIO_ERROR_UNSUPPORTED_SIZE, // The disk is too big to format as FAT16
    FILEIO_ERROR_WRITE_PROTECTED, // Card is write protected
    FILEIO_ERROR_FILE_UNOPENED, // File not opened for the write
    FILEIO_ERROR_SEEK_ERROR, // File location could not be changed successfully
    FILEIO_ERROR_BAD_CACHE_READ, // Bad cache read
    FILEIO_ERROR_FAT32_UNSUPPORTED, // FAT 32 - card not supported
    FILEIO_ERROR_READ_ONLY, // The file is read-only
    FILEIO_ERROR_WRITE_ONLY, // The file is write-only
    FILEIO_ERROR_INVALID_ARGUMENT, // Invalid argument
    FILEIO_ERROR_TOO_MANY_FILES_OPEN, // Too many files are already open
    FILEIO_ERROR_TOO_MANY_DRIVES_OPEN, // Too many drives are already open
    FILEIO_ERROR_UNSUPPORTED_SECTOR_SIZE, // Unsupported sector size
    FILEIO_ERROR_NO_LONG_FILE_NAME, // Long file name was not found
    FILEIO_ERROR_EOF // End of file reached
} FILEIO_ERROR_TYPE;

typedef enum {
    FILEIO_ATTRIBUTE_READ_ONLY = 0x01, // Read-only attribute.  A file with this attribute should not be written to.
    FILEIO_ATTRIBUTE_HIDDEN = 0x02, // Hidden attribute.  A file with this attribute may be hidden from the user.
    FILEIO_ATTRIBUTE_SYSTEM = 0x04, // System attribute.  A file with this attribute is used by the operating system and should not be modified.
    FILEIO_ATTRIBUTE_VOLUME = 0x08, // Volume attribute.  If the first file in the root directory of a volume has this attribute, the entry name is the volume name.
    FILEIO_ATTRIBUTE_LONG_NAME = 0x0F, // A file entry with this attribute mask is used to store part of the file's Long File Name.
    FILEIO_ATTRIBUTE_DIRECTORY = 0x10, // A file entry with this attribute points to a directory.
    FILEIO_ATTRIBUTE_ARCHIVE = 0x20, // Archive attribute.  A file with this attribute should be archived.
    FILEIO_ATTRIBUTE_MASK = 0x3F // Mask for all attributes.
} FILEIO_ATTRIBUTES;

typedef enum {
    FILEIO_SEEK_SET = 0, // Change the position in the file to an offset relative to the beginning of the file.
    FILEIO_SEEK_CUR, // Change the position in the file to an offset relative to the current location in the file.
    FILEIO_SEEK_END // Change the position in the file to an offset relative to the end of the file.
} FILEIO_SEEK_BASE;

typedef enum {
    FILEIO_OPEN_READ = 0x01, // Open the file for reading.
    FILEIO_OPEN_WRITE = 0x02, // Open the file for writing.
    FILEIO_OPEN_CREATE = 0x04, // Create the file if it doesn't exist.
    FILEIO_OPEN_TRUNCATE = 0x08, // Truncate the file to 0-length.
    FILEIO_OPEN_APPEND = 0x10 // Set the current read/write location in the file to the end of the file.
} FILEIO_OPEN_ACCESS_MODES;

typedef enum {
    FILEIO_FILE_SYSTEM_TYPE_NONE = 0, // No file system
    FILEIO_FILE_SYSTEM_TYPE_FAT12, // The device is formatted with FAT12
    FILEIO_FILE_SYSTEM_TYPE_FAT16, // The device is formatted with FAT16
    FILEIO_FILE_SYSTEM_TYPE_FAT32 // The device is formatted with FAT32
} FILEIO_FILE_SYSTEM_TYPE;

typedef struct {
    uint32_t baseClusterDir; // The base cluster of the file's directory
    uint32_t currentClusterDir; // The current cluster of the file's directory
    uint32_t firstCluster; // The first cluster of the file
    uint32_t currentCluster; // The current cluster of the file
    uint32_t size; // The size of the file
    uint32_t absoluteOffset; // The absolute offset in the file
    void * disk; // Pointer to a device structure
    uint16_t currentSector; // The current sector in the current cluster of the file
    uint16_t currentOffset; // The position in the current sector
    uint16_t entry; // The position of the file's directory entry in its directory
    uint16_t attributes; // The file's attributes
    uint16_t time; // The file's last update time
    uint16_t date; // The file's last update date
    uint8_t timeMs; // The file's last update time (ms portion)
    char name[FILEIO_FILE_NAME_LENGTH_8P3_NO_RADIX]; // The short name of the file

    struct {
        unsigned writeEnabled : 1; // Indicates a file was opened in a mode that allows writes
        unsigned readEnabled : 1; // Indicates a file was opened in a mode that allows reads

    } flags;
} FILEIO_OBJECT;

typedef enum {
    FILEIO_GET_PROPERTIES_NO_ERRORS = 0,
    FILEIO_GET_PROPERTIES_CACHE_ERROR,
    FILEIO_GET_PROPERTIES_DRIVE_NOT_MOUNTED,
    FILEIO_GET_PROPERTIES_CLUSTER_FAILURE,
    FILEIO_GET_PROPERTIES_STILL_WORKING = 0xFF
} FILEIO_DRIVE_ERRORS;

typedef enum {
    MEDIA_NO_ERROR, // No errors
    MEDIA_DEVICE_NOT_PRESENT, // The requested device is not present
    MEDIA_CANNOT_INITIALIZE // Cannot initialize media
} FILEIO_MEDIA_ERRORS;

typedef struct {
    FILEIO_MEDIA_ERRORS errorCode; // The status of the intialization FILEIO_MEDIA_ERRORS
    // Flags

    union {
        uint8_t value;

        struct {
            uint8_t sectorSize : 1; // The sector size parameter is valid.
            uint8_t maxLUN : 1; // The max LUN parameter is valid.
        } bits;
    } validityFlags;

    uint16_t sectorSize; // The sector size of the target device.
    uint8_t maxLUN; // The maximum Logical Unit Number of the device.
} FILEIO_MEDIA_INFORMATION;

typedef void (*FILEIO_DRIVER_IOInitialize)(void * mediaConfig);

typedef bool (*FILEIO_DRIVER_MediaDetect)(void * mediaConfig);

typedef FILEIO_MEDIA_INFORMATION * (*FILEIO_DRIVER_MediaInitialize)(void * mediaConfig);

typedef bool (*FILEIO_DRIVER_MediaDeinitialize)(void * mediaConfig);

typedef bool (*FILEIO_DRIVER_SectorRead)(void * mediaConfig, uint32_t sector_addr, uint8_t* buffer);

typedef uint8_t(*FILEIO_DRIVER_SectorWrite)(void * mediaConfig, uint32_t sector_addr, uint8_t* buffer, bool allowWriteToZero);

typedef bool (*FILEIO_DRIVER_WriteProtectStateGet)(void * mediaConfig);

typedef struct {
    FILEIO_DRIVER_IOInitialize funcIOInit; // I/O Initialization function
    FILEIO_DRIVER_MediaDetect funcMediaDetect; // Media Detection function
    FILEIO_DRIVER_MediaInitialize funcMediaInit; // Media Initialization function
    FILEIO_DRIVER_MediaDeinitialize funcMediaDeinit; // Media Deinitialization function.
    FILEIO_DRIVER_SectorRead funcSectorRead; // Function to read a sector of the media.
    FILEIO_DRIVER_SectorWrite funcSectorWrite; // Function to write a sector of the media.
    FILEIO_DRIVER_WriteProtectStateGet funcWriteProtectGet; // Function to determine if the media is write-protected.
} FILEIO_DRIVE_CONFIG;

typedef struct {
    char disk; /* pointer to the disk we are searching */
    bool new_request; /* is this a new request or a continued request */
    FILEIO_DRIVE_ERRORS properties_status; /* status of the last call of the function */

    struct {
        uint8_t disk_format; /* disk format: FAT12, FAT16, FAT32 */
        uint16_t sector_size; /* sector size of the drive */
        uint8_t sectors_per_cluster; /* number of sectors per cluster */
        uint32_t total_clusters; /* the number of total clusters on the drive */
        uint32_t free_clusters; /* the number of free (unused) clusters on drive */
    } results; /* the results of the current search */

    struct {
        uint32_t c;
        uint32_t curcls;
        uint32_t EndClusterLimit;
        uint32_t ClusterFailValue;
    } prv; /* intermediate values used to continue searches.  This
                         member should be used only by the FSGetDiskProperties()
                         function */

} FILEIO_DRIVE_PROPERTIES;

typedef union {

    struct {
        uint16_t day : 5; // Day (1-31)
        uint16_t month : 4; // Month (1-12)
        uint16_t year : 7; // Year (number of years since 1980)
    } bitfield;
    uint16_t value;
} FILEIO_DATE;

typedef union {

    struct {
        uint16_t secondsDiv2 : 5; // (Seconds / 2) ( 1-30)
        uint16_t minutes : 6; // Minutes ( 1-60)
        uint16_t hours : 5; // Hours (1-24)
    } bitfield;
    uint16_t value;
} FILEIO_TIME;

typedef struct {
    FILEIO_DATE date; // The create or write date of the file/directory.
    FILEIO_TIME time; // The create of write time of the file/directory.
    uint8_t timeMs; // The millisecond portion of the time.
} FILEIO_TIMESTAMP;

typedef struct {
    // Return values
    uint8_t shortFileName[13]; // The name of the file that has been found (NULL-terminated).
    uint8_t attributes; // The attributes of the file that has been found.
    uint32_t fileSize; // The size of the file that has been found (bytes).
    FILEIO_TIMESTAMP timeStamp; // The create or write time of the file that has been found.
    // Private Parameters
    uint32_t baseDirCluster;
    uint32_t currentDirCluster;
    uint16_t currentClusterOffset;
    uint16_t currentEntryOffset;
    uint16_t pathOffset;
    char driveId;
} FILEIO_SEARCH_RECORD;

int FILEIO_Initialize(void);
int FILEIO_Reinitialize(void);
typedef void (*FILEIO_TimestampGet)(FILEIO_TIMESTAMP *);
void FILEIO_RegisterTimestampGet(FILEIO_TimestampGet timestampFunction);
bool FILEIO_MediaDetect(const FILEIO_DRIVE_CONFIG * driveConfig, void * mediaParameters);
FILEIO_ERROR_TYPE FILEIO_DriveMount(char driveId, const FILEIO_DRIVE_CONFIG * driveConfig, void * mediaParameters);
int FILEIO_Format(FILEIO_DRIVE_CONFIG * config, void * mediaParameters, FILEIO_FORMAT_MODE mode, uint32_t serialNumber, char * volumeId);
int FILEIO_DriveUnmount(const char driveId);
int FILEIO_Remove(const char * pathName);
int FILEIO_Rename(const char * oldPathName, const char * newFileName);
int FILEIO_DirectoryMake(const char * path);
int FILEIO_DirectoryChange(const char * path);
uint16_t FILEIO_DirectoryGetCurrent(char * buffer, uint16_t size);
int FILEIO_DirectoryRemove(const char * pathName);
FILEIO_ERROR_TYPE FILEIO_ErrorGet(char driveId);
void FILEIO_ErrorClear(char driveId);
int FILEIO_Open(FILEIO_OBJECT * filePtr, const char * pathName, uint16_t mode);
int FILEIO_Close(FILEIO_OBJECT * handle);
int FILEIO_Flush(FILEIO_OBJECT * handle);
int FILEIO_GetChar(FILEIO_OBJECT * handle);
int FILEIO_PutChar(char c, FILEIO_OBJECT * handle);
size_t FILEIO_Read(void * buffer, size_t size, size_t count, FILEIO_OBJECT * handle);
size_t FILEIO_Write(const void * buffer, size_t size, size_t count, FILEIO_OBJECT * handle);
int FILEIO_Seek(FILEIO_OBJECT * handle, int32_t offset, int _base);
bool FILEIO_Eof(FILEIO_OBJECT * handle);
long FILEIO_Tell(FILEIO_OBJECT * handle);
int FILEIO_Find(const char * fileName, unsigned int attr, FILEIO_SEARCH_RECORD * record, bool newSearch);
int FILEIO_LongFileNameGet(FILEIO_SEARCH_RECORD * record, uint16_t * buffer, uint16_t length);
FILEIO_FILE_SYSTEM_TYPE FILEIO_FileSystemTypeGet(char driveId);
void FILEIO_DrivePropertiesGet(FILEIO_DRIVE_PROPERTIES* properties, char driveId);

#endif