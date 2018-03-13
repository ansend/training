
#include <stdio.h>
#include <string.h>

#include "file_sys.h"
#include "cos_buffer.h"
#include <string>
using namespace std;
AbsFile * AbsFile::pwd = NULL;

#include "cos_sys.h"

void test_dir_file()
{
    AbsFile * mf = new DirFile("3F00", FY_DIR);

    AbsFile * ef01 = new ElemFile("EF01", FY_BI);
    AbsFile * df01 = new DirFile("DF01", FY_DIR);

    assert(mf->get_type()   == FY_DIR);
    assert(ef01->get_type() == FY_BI);
    assert(df01->get_type() == FY_DIR);

    mf->add_file(ef01);
    mf->add_file(df01);

    //dynamic cast to DirFile from AbsFile
    DirFile* df_tmp = dynamic_cast<DirFile*>(mf);
    assert(df_tmp->size() == 2);
}

void test_cos_buff()
{
    Buffer buff;
    std::string test_str = "abcdefghkdkdkdkdkkdhjoeiqwfoefadfafdafdaf";

    buff.append(test_str.data(), test_str.size());

    std::string rstr = buff.read_all_as_string();

    assert(test_str.compare(rstr) == 0);

    std::string nstr = buff.read_as_string(10);

    char dest[20]={0};

    strncpy(dest,test_str.c_str(),10);

    assert(strncmp(test_str.c_str(), dest, 10) == 0);
    
}

void test_psam()
{

    Psam psam;

}
int main(int argc, char ** argv)
{
    printf(" trigger file sys main\n");  

    printf(" size of int %lu \n", sizeof(int));
    printf(" size of long %lu \n", sizeof(long));
    //test_dir_file();
    
    //test_cos_buff();
}




