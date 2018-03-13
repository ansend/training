// TIMES COS file system

#ifndef FILE_SYS_H_
#define FILE_SYS_H_

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>

#include "FileBuffer.h"

using namespace std;

enum
{
    FY_DIR  = 0,
    FY_BI   = 1,
    FY_REC  = 2
};

class AbsFile
{
    
    public:

        AbsFile(std::string name, uint8_t type): file_name(name), file_type(type){}
        virtual ~AbsFile(){}

        uint8_t         file_type;
        uint16_t        file_id;
        std::string     file_name;
 
        virtual bool    select_file(){;}
        virtual bool    add_file(AbsFile* file){;}
        virtual bool    remove_file(){;}
        virtual uint8_t get_type(){return file_type;}
     
    public:
        AbsFile*            parent;
        static AbsFile*     pwd;
};

class DirFile : public AbsFile
{
    public:
        DirFile(std::string name, uint8_t type) : AbsFile(name, type)
        {
            this->parent = NULL;
            printf("In Dir File system\n");
        }
        virtual ~DirFile(){;}
        virtual bool select_file(uint8_t fid)
        {
            for(std::vector<AbsFile*>::iterator it = childs.begin(); it != childs.end(); it++)
            {
                if((*it)->file_id == fid){

                    AbsFile::pwd = (*it);
                    return true;
                }
            }

            return false;

        }

        virtual bool add_file(AbsFile * file)
        {
            file->parent = this;
            childs.push_back(file); 
        }

        virtual bool remove_file(){;}
       
        std::vector<AbsFile*> childs;

    public:
        uint32_t size()
        {
            return childs.size();
        }

};

class ElemFile : public AbsFile
{
    public:
        ElemFile(std::string name, uint8_t type) : AbsFile(name, type)
        {
            this->parent = NULL;
            printf("In Abs File system\n");
        }
        virtual ~ElemFile(){;}

        virtual bool select_file()
        {
            //should not go here
            assert(0);
        }
        virtual bool add_file()
        {
            assert(0);
        }
        
        virtual bool remove_file()
        {
            assert(0);
        }
 
    public:
};

class BinFile : public ElemFile
{
    public:
        BinFile(std::string name, uint8_t type) : ElemFile(name, type)
        {
            printf("In BinFile system\n");
        }

        virtual ~BinFile(){;}

        void append(const char* data, size_t len)
        {
            buff.append(data, len);
        }
  
        void append(const void* data, size_t len)
        {
            buff.append(data, len);
        }

        std::string read_all_as_string()
        {
            buff.read_all_as_string();
        }
    
        std::string read_as_string(size_t len)
        {
            buff.read_as_string(len);
        }
    
    private:
        
        Buffer buff;
        
};

#else

#endif

