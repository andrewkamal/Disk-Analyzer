#include"data.h"

file::file()
{
    name="";
    directory_size=0;
    dir=false;
    path= (char*) malloc(256*sizeof(char));
}
ostream& operator<<(ostream& os, const file& dt)
{

    if(dt.dir)
        os << dt.size << " " <<dt.name<<" (dir)"<<endl;
    else
       os << dt.size << " " <<dt.name<<endl;
    return os;
}

bool  file:: operator< (const file &it)const
{// overloading operator
    if(size<it.size)// Less than
        return true;
    else if(size==it.size)
    {// if they are equal take check index to avoid removing dublicate ip
        if(name<it.name)
            return true;
    }
        else
            return false;
}

bool  file :: operator> (const file &it)const
{// Overloading operator
    if(size > it.size)// greater than
        return true;
    else if(size==it.size)
    { // if they are equal take check index to avoid removing dublicate ip
        if(name>it.name)
            return true;
    }
    else
        return false;
}
bool file:: operator!=(const file &it)const
{// Overloading operator
    if(size!=it.size)// not equal
        return true;
    else
        return false;
}
bool file:: operator ==(const file &it)const
{
    if(size==it.size)
        return true;
    else
        return false;

}

file::~file()
{
    // free(TREE);
}
