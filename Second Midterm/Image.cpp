#include <iostream>
#include <cstring>
using namespace std;
class Image
{
protected:
    char * ime;
    char sopstvenik [50];
    int shirina;
    int visina;
public:
    Image()
    {
        this->ime = new char [0];
        strcpy(this->ime,"untitled");
        strcpy(this->sopstvenik,"unknown");
        this->shirina = 800;
        this->visina = 800;
    }
    Image(char * ime)
    {
       this->ime = new char [strlen(ime)+1];
       strcpy(this->ime,ime);
    }
    Image(char * ime , char * sopstvenik)
    {
       this->ime = new char [strlen(ime)+1];
       strcpy(this->ime,ime);
       strcpy(this->sopstvenik,sopstvenik);
    }
    Image(char * ime , char * sopstvenik , int shirina , int visina)
    {
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->sopstvenik,sopstvenik);
        this->shirina = shirina;
        this->visina = visina;
    }
    Image(const Image & i)
    {
        this->ime = new char [strlen(i.ime)+1];
        strcpy(this->ime,i.ime);
        strcpy(this->sopstvenik,i.sopstvenik);
        this->shirina = i.shirina;
        this->visina = i.visina;
    }
    Image & operator = (const Image & i)
    {
        if(this != &i)
        {
        delete [] ime;
        this->ime = new char [strlen(i.ime)+1];
        strcpy(this->ime,i.ime);
        strcpy(this->sopstvenik,i.sopstvenik);
        this->shirina = i.shirina;
        this->visina = i.visina;
        }
        return * this;
    }
    ~Image()
    {
        delete [] ime;
    }
    virtual int fileSize()
    {
        return visina * shirina * 3;
    }
    friend ostream & operator << (ostream & out , Image & i)
    {
        out << i.ime << " " << i.sopstvenik << " " << i.fileSize() << endl;
        return out;
    }
    bool operator > (Image & i)
    {
        return this->fileSize() > i.fileSize();
    }
};
class TransparentImage : public Image
{
private:
    bool transparentnost;
public:
    TransparentImage()
    {
        transparentnost = false;
    }
    TransparentImage(char * ime , char * sopstvenik , int shirina , int visina , bool transparentnost) : Image(ime,sopstvenik,shirina,visina)
    {
        this->transparentnost = transparentnost;
    }
    int fileSize()
    {
        if(transparentnost == true)
        {
            return shirina * visina * 4;
        }
        else
        {
            return shirina * visina + (shirina * visina)/8;
        }
    }
    friend ostream & operator << (ostream & out , TransparentImage & ti)
    {
        out << ti.ime << " " << ti.sopstvenik << " " << ti.fileSize() << endl;
        return out;
    }
    bool operator > (TransparentImage & i)
    {
        return this->fileSize() > i.fileSize();
    }
};
class Folder
{
    char name [255];
    char user [50];
    Image * images [100];
    int n;
public:
    Folder(char * name = "" , char * user = "unknown")
    {
        strcpy(this->name,name);
        strcpy(this->user,user);
        this-> n = 0;
    }
    Folder(const Folder & f)
    {
        strcpy(this->name,f.name);
        strcpy(this->user,f.user);
        this-> n = f.n;
        for(int i = 0; i< f.n; i++)
        {
            this->images[i] = f.images[i];
        }
    }
    Folder & operator = (const Folder & f)
    {
        if(this != &f)
        {
        strcpy(this->name,f.name);
        strcpy(this->user,f.user);
        this-> n = f.n;
        for(int i = 0; i< f.n; i++)
        {
            this->images[i] = f.images[i];
        }
        }
        return * this;
    }
    int folderSize()
    {
        int suma = 0;
        for(int i = 0; i < n; i++)
        {
            suma += images[i]->fileSize();
        }
        return suma;
    }
    Image * getMaxFile()
    {
        Image * max = images[0];
        for(int i = 0; i < n; i++)
        {
            if(*images[i] > * max)
            {
                *max = *images[i];
            }
        }
        return max;
    }
    Folder & operator += (Image & im)
    {/*
        Image * tmp = new Image [n+1];
        for(int i = 0; i < n; i++)
        {
            tmp[i] = images[i];
        }
        tmp[n++] = im;
        delete [] images;
        images = tmp;
        return * this;*/
        this->images[n++]=&im;
        return *this;
    }
     Image *operator[](int index)
    {
        if(index<0 || index>=n) return 0;
        Image *max = images[index];
        return max;
    }
    friend ostream & operator << (ostream & out , Folder & f)
    {
        for(int i = 0; i < f.n; i++)
        {
            out << f.images[i];
        }
        out<<"--"<<endl;
        out<<"Folder size: " <<f.folderSize() << endl;
        return out;
    }
};
Folder & max_folder_size(Folder * folders , int n)
{
    int index = 0;
    int max = 0;
    for(int i = 0; i < n; i++)
    {
        if(folders[i].folderSize() > max)
        {
            max = folders[i].folderSize();
            index = i;
        }
    }
    return folders[index];
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
