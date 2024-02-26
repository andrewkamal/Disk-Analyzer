#include "newmain.h"
newmain::newmain()
{
    nbytes = 0;
    nfiles=0;
    ndirectories=0;
    v_size=0;
    t_size=0;
    totalsize=0;
}

void panic(char *filename,int line)
 {
    (void)fprintf(stderr,"\n?Panic in line %d of file %s\n",line,filename);
    (void)perror("Unexpected library error");
    abort();
 }
#define PANIC (panic(__FILE__,__LINE__))
 extern void panic();
 #define MAX_PATH 1000000

  /* This function will process 1 directory. It is called with
 3 * two arguments:
 4 * indent -- The number of columns to indent this directory
 5 * name -- The file name of the directory to process. This
 6 * is most often a relative directory
 7 *
 8 * The onedir function calls itself to process nested
 9 * directories
10 */

 BinarySearchTree<BSTNode<file>,file> * newmain::insertdirectory(file a,BSTNode<file> *n)
 {
    // AVLTree<file>* newTree= new AVLTree<file>;
    BinarySearchTree<BSTNode<file>,file> *newTree= new BinarySearchTree<BSTNode<file>,file>;
            //if(n!=NULL)
               newTree->setRoot(n);
         return newTree;
 }

 int newmain::recursive_delete(const char *dir)
 // https://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c
 {
     int ret = 0;
     FTS *ftsp = NULL;
     FTSENT *curr;

     // Cast needed (in C) because fts_open() takes a "char * const *", instead
     // of a "const char * const *", which is only allowed in C++. fts_open()
     // does not modify the argument.
     char *files[] = { (char *) dir, NULL };

     // FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
     //                in multithreaded programs
     // FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
     //                of the specified directory
     // FTS_XDEV     - Don't cross filesystem boundaries
     ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
     if (!ftsp) {
         fprintf(stderr, "%s: fts_open failed: %s\n", dir, strerror(curr->fts_errno));
         ret = -1;
         goto finish;
     }

     while ((curr = fts_read(ftsp))) {
         switch (curr->fts_info) {
         case FTS_NS:
         case FTS_DNR:
         case FTS_ERR:
             fprintf(stderr, "%s: fts_read error: %s\n",
                     curr->fts_accpath, strerror(curr->fts_errno));
             break;

         case FTS_DC:
         case FTS_DOT:
         case FTS_NSOK:
             // Not reached unless FTS_LOGICAL, FTS_SEEDOT, or FTS_NOSTAT were
             // passed to fts_open()
             break;

         case FTS_D:
             // Do nothing. Need depth-first search, so directories are deleted
             // in FTS_DP
             break;

         case FTS_DP:
         case FTS_F:
         case FTS_SL:
         case FTS_SLNONE:
         case FTS_DEFAULT:
             if (remove(curr->fts_accpath) < 0) {
                 fprintf(stderr, "%s: Failed to remove: %s\n",
                         curr->fts_path, strerror(curr->fts_errno));
                 ret = -1;
             }
             break;
         }
     }

 finish:
     if (ftsp)
     {
         fts_close(ftsp);
     }

     return ret;
 }

void newmain::insertFile(file a, BinarySearchTree<BSTNode<file>,file>*t)
{
    t->insert(a);
}


long long  newmain::onedir(short indent,char *name,BinarySearchTree<BSTNode<file>,file>* Ntree)
{
    Ntree->size=0;
    int d_size=0;
    file a;
    a.path=name;
    DIR *current_directory; /* pointer for readdir */
    struct dirent *this_entry; /* current directory entry */
    struct stat status; /* for the stat() function */
    char cwd[MAX_PATH+1];  /*save current working
    17 * directory
    18 */
    int i;
    /* Now open the directory for reading */
    current_directory = opendir(name);
    if (current_directory == NULL)
    {
        (void)perror("Can not open directory");
        return 0;
    }
    /* Remember the current working directory and connect to
    36 * new directory. We will then be able to stat() the
    37 * files without building a prefix.
    38 */
    if (getcwd(cwd,MAX_PATH+1) == NULL) PANIC;
        if (chdir(name) != 0) PANIC;

    /* Now, look at every entry in the directory */
        while ((this_entry = readdir(current_directory))!= NULL)
        {
            /*If entries for dot or dot-dot exist, one entry will be returned
            for dot and one entry will be returned for dot-dot;
            otherwise they will not be returned */
            /* Ignore "." and ".." or we will get confused */
            if ((strcmp(this_entry->d_name,".") != 0) && (strcmp(this_entry->d_name,"..") != 0))
            {
                if (stat(this_entry->d_name,&status) != 0)
                        continue;

                if (S_ISREG(status.st_mode))
                {/* If this is a normal file */
                    a.name=this_entry->d_name;
                    a.size=(long)status.st_size;
                    a.dir=false;
                    insertFile(a,Ntree);
                    nbytes += (long)status.st_size;
                    Ntree->size=nbytes;
                    nfiles++;
                }
                 else
                 if (S_ISDIR(status.st_mode))
                 {
                // /* If this is a nested directory,process it */
                    BSTNode<file> *next=new BSTNode<file>;
                    next->r= true;
                    a.name=this_entry->d_name;
                    a.dir=true;
                    BinarySearchTree<BSTNode<file>,file>* NewTree= new BinarySearchTree<BSTNode<file>,file>;
                    NewTree= insertdirectory(a,next);
                    char *str= (char*) malloc(256*sizeof(char));
                    memset(str,0,sizeof(char));
                    strcat(str,name);
                    strcat(str,"/");
                    strcat(str,this_entry->d_name);
                    a.path=str;
                    nbytes+=status.st_size;
                    Ntree->size=nbytes;
                    a.Ptr_to_Directory=next;
                    a.tree= NewTree;
                    a.my_tree=Ntree;
                    Ntree->insert(a);
                    ndirectories++;
                 }

            }

        }


        /* All done. Close the directory */
        if (closedir(current_directory) != 0) PANIC;
        /* change back to the "previous" directory */
        if (chdir(cwd) != 0) PANIC;

 return nbytes;

}


void newmain::traverseASC(BSTNode<file>*n)
{
    if ( n == NULL) return ; // recursivly looping until reach a leaf
        traverseASC(n->getLeft());// recursion from the left tree to get the minimum
    file a= n->getItem();
    bool flag;
    ofstream myfile;

    if(a.dir)
    {
        v_size=0;
        onedir(2,a.path,a.tree);
        traverseASC(a.Ptr_to_Directory);

        v_size=a.tree->size;
        a.size=v_size-a.my_tree->size;

        if(a.size<0)
            a.size=0;
        a.my_tree->size+=a.size;
        n->setItem(a);
    }
    traverseASC(n->getRight());// recursion

}

string newmain::utility (string temp)
{
    string ret;
    for (int i=0; i<temp.size(); i++)
    {
        if (temp.at(i)=='/')
            continue;
        else
        {
            ret+=temp.at(i);
        }


    }
    return ret;

}

void newmain::traverseChild(BSTNode<file>*n,ofstream &myfile,string cwd)
{

    if ( n == NULL) return ; // recursivly looping until reach a leaf
        traverseChild(n->getLeft(),myfile,cwd);// recursion from the left tree to get the minimum
        file a=n->getItem();
        if(a.name!="")
            myfile<<a.name<<" "<<a.size<<endl;

          if (a.dir==1)
          {

            string temp= utility(a.path);
            temp=temp+".txt";
            string s=cwd+temp;
            ofstream myfile(s);
            traverseChild(a.Ptr_to_Directory,myfile,cwd);
          }

    traverseChild(n->getRight(),myfile,cwd);// recursion

}

void newmain::run(char * name)
{

    char cwd[PATH_MAX];
 if (getcwd(cwd, sizeof(cwd)) != NULL)
 {
     printf("Current working dir: %s\n", cwd);
 }
 else
 {
     perror("getcwd() error");
     return ;
 }
 cw= cwd;
 cw+="/files/";
 const char * c = cw.c_str();
  if (mkdir("files", 0777) == -1)
   {
      recursive_delete(c);
      mkdir("files" ,0777);
   }

  else
      cout << "Directory created";


        int indent =2;
        long long int size=0;
        BinarySearchTree<BSTNode<file>,file>*tree1= new BinarySearchTree<BSTNode<file>,file>;
        onedir(indent,name,tree1);
        traverseASC(tree1->getRoot());
        string temp= utility(name);
        temp=temp+".txt";
        string st=cw+temp;
        ofstream myfile(st);
        traverseChild(tree1->getRoot(),myfile,cw);

        size=tree1->size;
        printf("total size =""%" PRIu64 "\n", size);
        printf(" total files = %d\n total directories = %d\n",nfiles,ndirectories);
}

