#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

// -----------------------------------------

#define FILE_READ std::ios::in
#define FILE_WRITE (std::ios::out | std::ios::app | std::ios::ate)

class FileLogger 
{
public:

    // General string for store error message string
    std::string errorMessage;

    // Recorder frequency [Hz].
    int recFrq;

    // Record duration time. value in [sec] indicate how much time record at past.
    int recDur;

    // Time for sdcard record events. [us]
    uint64_t T;  

    // Time for sdcard record reset events. [us]             
    uint64_t T_Reset;         

    // Constructor 
    //@param record_frequency: recorder frequency [Hz].
    //@param record_duration: record duration time. value in [sec] indicate how much time record at past.
    FileLogger(uint16_t record_frequency = 100, uint32_t record_duration = 3600);
    
    // Set the root directory for file operations.
    bool setDir(const std::filesystem::path& directory_address = "./");

    // Open a file with name address and mode write/read.
    bool open(const std::string& file_name, std::ios_base::openmode mode = FILE_READ);

    // Write data to the file.
    //@param data: the byte, char, or string (char *) to write.
    size_t write(uint8_t byte);

    // Write data to the file.
    //@param buf: an array of characters or bytes.
    //@param len: the number of elements in buf.
    size_t write(const uint8_t* buf, size_t size);

    // Print data to the file, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void print(const std::string& data);

    // Print data, followed by a carriage return and newline, to the File, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void println(const std::string& data);

    // Print data to the file, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void print(int data);

    // Print data, followed by a carriage return and newline, to the File, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void println(int data);

    // Print data to the file, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void print(double data);

    // Print data, followed by a carriage return and newline, to the File, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void println(double data);

    // Print data to the file, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void print(const char* data);

    // Print data, followed by a carriage return and newline, to the File, which must have been opened for writing.
    // @param data: the data to print (char, byte, int, long, or string).
    void println(const char* data);

    // Check file that is open or not.
    int availableForWrite();

    // Read one charecter from file and move file pointer one step forward.
    int read();

    // Read nbyte charecter from file and move file pointer nbyte step forward.
    int read(void* buf, uint16_t nbyte);

    // Read all contain of file and return it in a string format.
    std::string readAll();
    
    /*
        Read a byte from the file without advancing to the next one. 
        That is, successive calls to peek() will return the same value, as will the next call to read()
    */
    int peek();

    // Seek to a new position in the file, which must be between 0 and the size of the file (inclusive).
    bool seek(uint32_t pos);

    // Get the current position within the file (i.e. the location to which the next byte will be read from or written to).
    uint32_t position();

    // Get the size of the file.
    uint32_t size();

    // Check if there are any bytes available for reading from the file.
    int available();
    
    // Ensures that any bytes written to the file are physically saved to the SD card. This is done automatically when the file is closed.
    void flush();

    // Close the file, and ensure that any data written to it is physically saved to the SD card.
    void close();

    explicit operator bool() const;

    // Returns the file name
    const std::string& name() const;

    // Directories (or folders) are special kinds of files, this function reports if the current file is a directory or not.
    bool isDirectory() const;

    // This function will bring you back to the first file in the directory, used in conjunction with openNextFile().
    void rewindDirectory();

    // Finalize and clean up
    void end();

    // Tests whether a file or directory exists on the SD card.
    bool exists(const std::string& filepath);

    // Create a directory on the SD card. This will also create any intermediate directories that don’t already exists; e.g. SD.mkdir("a/b/c") will create a, b, and c.
    bool mkdir(const std::string& filepath);

    // Remove a file from the SD card.
    bool remove(const std::string& filepath);

    // Remove a directory from the SD card. The directory must be empty.
    bool rmdir(const std::string& filepath);

    // Reset file pointer to position 0. Reset value of line numer of pointer to 0.
    void resetLineNum(void);

private:
    std::fstream _fileStream;  // Internal file stream handler
    std::filesystem::path _root = "./"; // Handle for the root directory
    std::string _currentFileName; // Store the current file name

    // logger cursor line number.
    uint64_t _lineNum;

    // Helper function to get parent directory
    std::fstream getParentDir(const std::string& filepath, int* indx);
    int fileOpenMode;
};

#endif
