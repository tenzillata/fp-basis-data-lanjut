#include<iostream>
#include <stdlib.h>
using namespace std;


struct treeNode
{
    int nik; 
    string nama, alamat, ttl;
    treeNode *left;  
    treeNode *right; 
};

struct datapenduduk{
	string nik;
	string nama;
	string ttl;
	int nomor;
};

struct datapenduduk penduduk[100];


treeNode *SearchMin(treeNode *node) 
{
   
    if (node == NULL)
    {
   
        return NULL;
    }
    if (node->left)
        return SearchMin(node->left);
    else
        return node;
}

treeNode *masok(treeNode *node, int nik, string nama, string ttl, string alamat) 
{
    if (node == NULL) 
    {
        treeNode *temp; 
        temp = new treeNode;
        temp->nik = nik;                
        temp->nama = nama; 
		temp->ttl = ttl;             
        temp->alamat = alamat;           
        temp->left = temp->right = NULL; 
        return temp;                    
    }
    if (nik > (node->nik)) 
    {
        node->right = masok(node->right, nik, nama, ttl, alamat);
    }
    else if (nik < (node->nik)) 
    {
        node->left = masok(node->left, nik, nama, ttl, alamat);
    }
    return node; 
}

treeNode *hapus(treeNode *node, int nik) 
{
    treeNode *temp;
    if (node == NULL)
    {                                                 
        cout << "Data NIK Tidak Ditemukan!";
    }
    else if (nik < node->nik) 
    {
        node->left = hapus(node->left, nik); 
    }
    else if (nik > node->nik) 
    {
        node->right = hapus(node->right, nik); 
    }
    else
    {

        if (node->right && node->left) 
        {
            temp = SearchMin(node->right);
            node->nik = temp->nik;
          
            node->right = hapus(node->right, temp->nik);
        }
        else
        {
            temp = node;
            if (node->left == NULL)       
                node = node->right;      
            else if (node->right == NULL) 
                node = node->left;        
            free(temp);                   
        }
    }
    return node; 
}

void tampil(treeNode *node)
{
    if (node == NULL) 
    {
        return;
    }
    tampil(node->left);
    
    cout << "\nDATA PENDUDUK" << endl;
    cout << "Nomor Induk Kependudukan           : " << node->nik << endl;
    cout << "Nama Lengkap                       : " << node->nama << endl;
    cout << "Tempat/Tgl Lahir                   : " << node->ttl << endl;
    cout << "Alamat                             : " << node->alamat << endl;
    tampil(node->right);
}


treeNode *cari(treeNode *node, int nik) 
{
    if (node == NULL) 
    {
        return NULL;
    }
    if (nik > node->nik) 
    {
        return cari(node->right, nik); 
    }
    else if (nik < node->nik) 
    {
        return cari(node->left, nik); 
    }
    else
    {
        return node;
    }
}

void QueueNode(treeNode *node) 
{
    if (node == NULL) 
    {
        return;
    }
    QueueNode(node->left);
    cout << node->nik << " ";
    QueueNode(node->right);
}

template <class X>
class AVL{
    public:
        class node{
            public:
                X key;
                int height;
                node * left;
                node * right;
                node(X y){
                    height = 1;
                    key = y;
                    left = NULL;
                    right = NULL;
                }
        };
        node * root = NULL;
        int n;
        
        void insert(X z){
            root=insertAVL(root, z);
        }
        
        void remove(X z){
            root=removeAVL(root, z);
        }
        
        node * search(X z){
            return searchAVL(root,z);
        }
        
        void view(){
            viewavl(root);
            cout<<endl;
        }
    private:
        int height(node * head){
            if(head==NULL) return 0;
            return head->height;
        }
        
        node * rightRotation(node * head){
            node * newhead = head->left;
            head->left = newhead->right;
            newhead->right = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        node * leftRotation(node * head){
            node * newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        void viewavl(node * head){
            if(head==NULL) return ;
            viewavl(head->left);
            cout << "Registrasi KTP Ke " << head->key<< "\n";
            int temp = head->key;
            cout << "--------------------------------------------------\n" << endl;
            cout << "NIK              : " << penduduk[temp].nik << endl;
            cout << "Nama Lengkap     : " << penduduk[temp].nama  << endl;
            cout << "Tempat/Tgl Lahir : " << penduduk[temp].ttl << endl;
            cout << endl;
            viewavl(head->right);
        }

        node * insertAVL(node * head, X z){
            if(head==NULL){
                n+=1;
                node * temp = new node(z);
                return temp;
            }
            if(z < head->key) head->left = insertAVL(head->left, z);
            else if(z > head->key) head->right = insertAVL(head->right, z);
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(z < head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if(z > head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        
        node * removeAVL(node * head, X z){
            if(head==NULL) return NULL;
            if(z < head->key){
                head->left = removeAVL(head->left, z);
            }else if(z > head->key){
                head->right = removeAVL(head->right, z);
            }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeAVL(head->right, r->key);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(height(head->left) >= height(head->right)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(height(head->right) >= height(head->left)){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        
        node * searchAVL(node * head, X z){
            if(head == NULL) return NULL;
            X y = head->key;
            if(y == z) return head;
            if(y > z) return searchAVL(head->left, z);
            if(y < z) return searchAVL(head->right, z);
        }
};


int bst(){
    int pilihan, atas, opsi, opsi2;         
    string nama, alamat, ttl;;
    treeNode *root = NULL, *temp; 
    input:
    system("CLS");
    cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *                  PROGRAM                   *"<<endl;
    cout<<"                                       *               PEMBUATAN KTP                *"<<endl;
    cout<<"                                       ******************DAFTAR MENU*****************"<<endl;
    cout<<"                                       *1. Input Data                               *"<<endl;
    cout<<"                                       *2. Delete Data                              *"<<endl;
    cout<<"                                       *3. Tampilkan Data                           *"<<endl;
    cout<<"                                       *4. Cari Data                                *"<<endl;
    cout<<"                                       *5. Keluar                                   *"<<endl;
    cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *Silahkan Input Pilihan Anda : ";
	cin>>pilihan;
	switch (pilihan){
		case 1:
                cout << "Masukan NIK                       : " ; 
                cin >> atas;
                cout << "Masukan Nama Lengkap              : " ; 
                cin.ignore(); getline(cin, nama);
                cout << "Masukan Tempat/Tgl Lahir          : " ; 
                getline(cin, ttl);
                cout << "Masukan Alamat                    : " ; 
                getline(cin, alamat);
                root = masok(root, atas, nama, ttl, alamat);
                system("PAUSE");    
                goto input;
                break;
		case 2:
                cout << "Masukan NIK : "; 
                cin >> atas;
                root = hapus(root, atas); 
                cout << " " << endl<<endl;
                system("PAUSE");
                system("CLS");   
                cout << "Setelah Dihapus "<<endl; 
                cout << "No NIK : ";
                QueueNode(root);
                cout << " " << endl;
                system("PAUSE");
                goto input;
                break;
		case 3:
				system("CLS");
                cout << "Data NIK : "<<endl;
                tampil(root); 
                cout << endl;
                system("PAUSE");
                goto input;
                break;
		case 4:
				cout << " Masukkan NIK Yang Dicari : ";
                cin >> atas;
                temp = cari(root, atas);
                if (temp == NULL)
                    {
                        cout <<"DATA NIK YANG ANDA CARI TIDAK ADA DI DATABASE!"<<endl;
                        system("PAUSE");;
                    }
                    else
                    {  
                        cout <<"DATA NIK YANG ANDA CARI TERDAFTAR DI DATABASE"<<endl;
                        system("PAUSE");
                    }
                    cout << endl;
                    system("cls");
                    goto input;
		case 5:
		cout<<"Apakah Anda Ingin Keluar?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi2;
		system("cls");
		if (opsi2==1){
			cout<<"SAMPAI JUMPA :)";
			exit(0);;
		}else{
			goto input;
		}
		default:
		cout<<"Pilihan Tidak Tersedia!"<<endl;
		system("pause");
		system("cls");	
		cout<<"Apakah Anda Ingin Melanjutkan?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi;
		system("cls");
		if (opsi==1){
			goto input;
		}else{
			cout<<"SAMPAI JUMPA :)";
			exit(0);
		}		
			
}
}

int avl(){
	int pilihan, opsi, opsi2, jml, i, nomor; 
    treeNode *root = NULL, *temp; 
    AVL<float> a;
    input:
    system("CLS");
    cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *                  PROGRAM                   *"<<endl;
    cout<<"                                       *               PEMBUATAN KTP                *"<<endl;
    cout<<"                                       ******************DAFTAR MENU*****************"<<endl;
    cout<<"                                       *1. Input Data                               *"<<endl;
    cout<<"                                       *2. Delete Data                              *"<<endl;
    cout<<"                                       *3. Tampilkan Data                           *"<<endl;
    cout<<"                                       *4. Cari Data                                *"<<endl;
    cout<<"                                       *5. Keluar                                   *"<<endl;
    cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *Silahkan Input Pilihan Anda : ";
	cin>>pilihan;
	switch (pilihan){
		case 1:
				cout << "Jumlah Data : " ;
		    	cin  >> jml;
				cin.ignore();
				system ("cls");
				
		    	for(i = 0; i<jml; i++) 
				{
		    		cout << "-----------------------------------------------------------"   << endl;
		    		cout << "Data Penduduk Ke - " << i+1 << endl;
		    		cout << "-----------------------------------------------------------\n" << endl;
		    		cout << "Nomor Registrasi KTP : ";
		    		cin  >> nomor;
		    		cin.ignore();
					cout << "NIK                  : ";
		    		getline(cin, penduduk[nomor].nik);
		    		cout << "Nama Lengkap         : ";
		    		getline(cin, penduduk[nomor].nama);
		    		cout << "Tempat/Tgl Lahir     : ";
		    		getline(cin, penduduk[nomor].ttl);
		    		
		    		penduduk[nomor].nomor = nomor;
		    		
		    		a.insert(nomor);
		    		cin.ignore();
					cout << endl;			
				}
                system("PAUSE");    
                goto input;
                break;
		case 2:
                cout << "Nomor Registrasi KTP Yang Ingin Dihapus : ";
				cin  >> nomor;
				cout << "------------------------------------------------------------ \n" << endl;
				
				if(nomor == penduduk[nomor].nomor) 
				{
					a.remove(nomor);
					cout << "Data Penduduk Berhasil Dihapus" << endl;	
				}
				else 
				{
					cout << "Data Tidak Ada!" << endl;
	 			}
	 			
                system("PAUSE");
                goto input;
                break;
		case 3:
				a.view();
                system("PAUSE");
                goto input;
                break;
		case 4:
				cout << "Masukkan Nomor Registrasi KTP : ";
				cin  >> nomor;
				cout << "-------------------------------------------------------------\n" << endl;
				if(nomor == penduduk[nomor].nomor) {
					cout << "-----------------------------------------------------------" << endl;
					cout << "Nomor Registrasi KTP  "    << nomor << endl;
					cout << "----------------------------------------------------------- \n" << endl;
					cout << "NIK              : " << penduduk[nomor].nik << endl;
					cout << "Nama Lengkap     : " << penduduk[nomor].nama  << endl;
					cout << "Tempat/Tgl Lahir : " << penduduk[nomor].ttl  << endl;
				}
				else {
					cout << "Data Tidak Ada!" << endl;
				}	
                    system("pause");
                    goto input;
		case 5:
		cout<<"Apakah Anda Ingin Keluar?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi2;
		system("cls");
		if (opsi2==1){
			cout<<"SAMPAI JUMPA :)";
			exit(0);;
		}else{
			goto input;
		}
		default:
		cout<<"Pilihan Tidak Tersedia!"<<endl;
		system("pause");
		system("cls");	
		cout<<"Apakah Anda Ingin Melanjutkan?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi;
		system("cls");
		if (opsi==1){
			goto input;
		}else{
			cout<<"SAMPAI JUMPA :)";
			exit(0);
		}		
			
}
}
	
int menu()
{
	int pilihan;
	int opsi, opsi2;
	input:
    cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *                  PROGRAM                   *"<<endl;
    cout<<"                                       *               PEMBUATAN KTP                *"<<endl;
    cout<<"                                       *                                            *"<<endl;
    cout<<"                                       ******************DAFTAR MENU*****************"<<endl;
    cout<<"                                       *1. BST                                      *"<<endl;
    cout<<"                                       *2. AVL                                      *"<<endl;
    cout<<"                                       *3. Keluar Dari Program                      *"<<endl;
    cout<<"                                       **********************************************"<<endl;
    cout<<"                                       *Silahkan Input Pilihan Anda : ";
	cin>>pilihan;
	switch (pilihan){
		case 1:
			bst();
			break;
		case 2:
			avl();
			break;	
		case 3:
		cout<<"Apakah Anda Ingin Keluar?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi2;
		system("cls");
		if (opsi2==1){
			cout<<"SAMPAI JUMPA :)";
			exit(0);;
		}else{
			goto input;
		}		
			
		default:
		cout<<"Pilihan Tidak Tersedia!"<<endl;
		system("pause");
		system("cls");	
		cout<<"Apakah Anda Ingin Melanjutkan?"<<endl;
		cout<<"1. Ya"<<endl;
		cout<<"2. Tidak"<<endl;
		cout<<"Input Pilihan Anda : ";
		cin>>opsi;
		system("cls");
		if (opsi==1){
			goto input;
		}else{
			cout<<"SAMPAI JUMPA :)";
			exit(0);
		}		
			
}
}

loading(){
	cout<<"\n\n\n\t\t\t\tSedang Loading\n";
      cout<<"\t\t\t\tMohon Ditunggu\n";
      cout<<"\t\t\t\tKANTOR KTP\n\n";
     
      cout<<"\t\t\t\t";
      for (int i=0;i<=30;i++)
      cout<<"*"
         <<"\r"
         <<"\t\t\t\t";
      for (int i=0;i<=30;i++) {
      cout<<"*";
      for (int j=0;j<=1e8;j++); 
      }
        cout<<"\n\n\n\t\t\t\t\n\n";
        cout<<"LOADING SELESAI"<<endl;
        system ("pause");
        system("cls"); 
}

login(){
   int i;  
   string password_input, username_input;  
   
   cout << "                                      ==========================================\n";    
   cout << "                                                     LOGIN ADMIN                \n";    
   cout << "                                      ==========================================\n";  
   cout << "                                                   SELAMAT DATANG               \n";  
   cout << "                                      ==========================================\n\n";
   string username ="12345";    
   string password = "12345";    
   string login ;
   i = 1;    
   
   do {        
       cout << "Username = "; cin>>username_input;        
       cout << "Password = "; cin>>password_input;        
       if (username_input == username && password_input == password) {    
	   	   system("cls");        
           cout << " ================\n";            
           cout << "| Login Berhasil |" << endl;                        
           cout << " ================\n\n";  
           i = 4;
           login = "berhasil"; 
		   system("pause");
		   system("cls");       } 
       else {            
           cout << "\n===========================\n";            
           cout << "Username / Password Salah! ("<<i<<"x)\n";
		   cout << "=============================\n\n";            
           i = i +1;
       }   
    } while (i <= 3);
	
    if(login != "berhasil"){
       cout<<"Anda telah 3x salah login.\n";       
       cout<<"Silahkan Hubungi Admin. Terima Kasih..\n\n";   
	   exit(0);   
	}   

}

int main(){
	system("color 0a");
	loading();
	login();
	menu();
}
