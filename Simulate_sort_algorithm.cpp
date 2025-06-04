#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include <time.h>

#define MAX 100
#define INPUT "text.txt"

#define Y 4
//Hàm
void readfile();
void INPoint(struct toado m[MAX],int size);
void vekhung();
void quickSortMidPivot( int left, int right);
void mouse();
void keyboard();
void selection();
void bubble();
void insertion();
void vediem(struct toado m[MAX],int color);
void vediem1(struct toado points[MAX],int size);
void scanline(int x1, int y1, int x2, int y2, int fillColor);
void shuffle(struct toado point[MAX],int size);
void quick(int l, int r);
void todiem(struct toado point, int color, int n);
//BienToanCuc
int sodinh;
FILE *fp;
char buffer[10];
int enable_click=1;
int X;



struct toado{
	int value;
};

struct toado td[MAX];
//doc file
void readfile(){
	fp=fopen(INPUT,"r");
	if(fp==NULL){printf("File not Found");return;
	}
	fscanf(fp,"%d",&sodinh);
	printf("\n so phan tu can sx la %d \n",sodinh);
	for(int i=0;i<sodinh;i++){
		fscanf(fp," %d",&td[i].value);
	}
	fclose(fp);
}
//ham ngau nhien
void randomArray(struct toado point[MAX], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        point[i].value = rand() % 100 + 1; 
    }
}
//ve giao dien
void vekhung(){
	
    
    setcolor(5);
    setlinestyle(0, 1, 3);
    rectangle(10, 10, 1380, 610);  

  
  setcolor(11 );
    rectangle(1250, 40, 1350, 100);
    settextstyle(2, 0, 7);
    outtextxy(1270, 60, "Shuffle");

  
     setcolor(10);
 rectangle(75, 640, 275, 700);  // Nút "Read File"
    settextstyle(2, 0, 9);
    outtextxy(95, 655, "Read File");

    rectangle(425, 640, 625, 700);  // Nút "Try Again"
    settextstyle(2, 0, 9);
    outtextxy(440, 655, "Try Again");

    rectangle(775, 640, 975, 700);  // Nút "Key Board"
    settextstyle(2, 0, 9);
    outtextxy(785, 655, "Key Board");

    rectangle(1125, 640, 1325, 700);  // Nút "Random"
    settextstyle(2, 0, 9);
    outtextxy(1145, 655, "Random");
	setcolor(13);
    // Các l?a ch?n s?p x?p
    rectangle(75, 740, 275, 800);
    settextstyle(2, 0, 9);
    outtextxy(95, 752, "Selection");

    rectangle(425, 740, 625, 800);
    settextstyle(2, 0, 9);
    outtextxy(465, 752, "Bubble");

    rectangle(775, 740, 975, 800);
    settextstyle(2, 0, 9);
    outtextxy(800, 752, "Insertion");
     
	rectangle(1125, 740, 1325, 800);
    settextstyle(2, 0, 9);
    outtextxy(1170, 752, "Quick");

}
//xu ly click chuot
void mouse(){
    int x, y;
    while(enable_click){
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
if (x >= 75 && x <= 275 && y >= 640 && y <= 700) {
                printf("Read File\n");
                readfile();  
                cleardevice();
                vekhung();
                vediem1(td, sodinh); 
            }

         
            if (x >= 425 && x <= 625 && y >= 640 && y <= 700) {
                printf("Try Again\n");
                enable_click = 1;
                cleardevice();  
                vekhung();  
               
            
            }

            
            if (x >= 775 && x <= 975 && y >= 640 && y <= 700) {
                printf("Key Board\n");
                cleardevice();
                vekhung();
                keyboard();  
                vediem1(td, sodinh); 
            }

           
            if (x >= 1125 && x <= 1325 && y >= 640 && y <= 700) {
                printf("Random\n");
                cleardevice();
                vekhung();
                sodinh=10;
                randomArray(td, sodinh);  
                vediem1(td, sodinh);  
            }
			if(x >= 1250 && x <= 1350 && y >= 40 && y <= 100){
                printf("Shuffle\n");
                cleardevice();
                vekhung(); 
               	shuffle(td,sodinh);  
                vediem1(td, sodinh);
            }
        
            if(x >= 75 && x <= 275 && y >= 740 && y <= 800){
                printf("Selection sort\n");
                enable_click = 0;
                setcolor(4);  
                rectangle(75, 740, 275, 800);
                settextstyle(2, 0, 9);
                outtextxy(95, 752, "Selection");
                selection();  
            }

            
            if(x >= 425 && x <= 625 && y >= 740 && y <= 800){
                printf("Bubble sort\n");
                enable_click = 0;
                setcolor(4);  
                rectangle(425, 740, 625, 800);
                settextstyle(2, 0, 9);
                outtextxy(465, 752, "Bubble");
                bubble(); 
            }

         
            if(x >= 775 && x <= 975 && y >= 740 && y <= 800){
                printf("Insertion sort\n");
                enable_click = 0;
                setcolor(4);  
                rectangle(775, 740, 975, 800);
                settextstyle(2, 0, 9);
                outtextxy(800, 752, "Insertion");
                insertion();  //
            }

       
            if(x >= 1125 && x <= 1325 && y >= 740 && y <= 800){
                printf("Quick sort\n");
                enable_click = 0;
                setcolor(4);  // Màu d? cho l?a ch?n
                rectangle(1125, 740, 1325, 800);
                settextstyle(2, 0, 9);
                outtextxy(1170, 752, "Quick");
                quickSortMidPivot(0,sodinh-1);
                cleardevice();
                vekhung();
                vediem1(td,sodinh);
                 for (int i = 0; i < sodinh; i++) {
	        todiem(td[i], 9, i);
	    }
               enable_click=1;
               
            }
        }

        // xu ly su kien khi muon thoat ra thi chuot phai
        if(ismouseclick(WM_RBUTTONDOWN)){
            getmouseclick(WM_RBUTTONDOWN, x, y);
            printf("\nExiting..\n");
            closegraph();
            break;
        }
        delay(100); 
    }
}
//hàm tron
void shuffle(struct toado point[MAX], int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = point[i].value;
        point[i].value = point[j].value;
        point[j].value = temp;
    }
}
//doc tu ban phim
void keyboard(){
	fp=fopen(INPUT,"r");
	if(fp==NULL){printf("File not Found");return;
	}
	fscanf(fp,"%d",&sodinh);
	printf("Xin moi nhap du lieu (Mac dinh la 10 phan tu : 0<X<100 )\n");
	for(int i=0;i<sodinh;i++){
		printf("td[%d].value = ",i);
		scanf("%d",&td[i].value);
	}
	fclose(fp);
}
//to mau
void scanline(int x1, int y1, int x2, int y2, int Color) {
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            putpixel(x, y,Color); 
        }
    }
}
//ve 1 diem
void vediem(struct toado point, int color, int n){
    setcolor(color);
    X=1000/sodinh;
    
    rectangle(200 + X * n, 500 - point.value * Y, 200 + X * (n + 1), 500); 
    settextstyle(1, 0, 3);
    if(point.value>=10){
    	outtextxy(200 + X * n+6 , 500 - point.value * Y - 30, itoa(point.value, buffer, 10));
	}
    else outtextxy(200 + X * n+16 , 500 - point.value * Y - 30, itoa(point.value, buffer, 10));
   
}
//to mau 1 diem
void todiem(struct toado point, int color, int n){
    setcolor(color);
    rectangle(200 + X * n, 500 - point.value * Y, 200 + X * (n + 1), 500); 
    settextstyle(1, 0, 3);
    if(point.value>=10){
    	outtextxy(200 + X * n+6 , 500 - point.value * Y - 30, itoa(point.value, buffer, 10));
	}
	
    else outtextxy(200 + X * n+16 , 500 - point.value * Y - 30, itoa(point.value, buffer, 10));
   scanline(201+X*n,500-point.value*Y,199+X*(n+1),500,color);
}
//ve mang
void vediem1(struct toado points[MAX],int size){
	for(int i=0;i<size;i++){
		vediem(points[i],15,i);
		
	}
}
void vediem2(struct toado points[MAX],int size,int minsize){
	for(int i=size-1;i>minsize;i--){
		vediem(points[i],2,i);
		
	}
}
//xoa diem sau khi thay doi
void xoadiem(struct toado point,int color,int n){
	setcolor(color);
    rectangle(200 + X * n, 500 - point.value * Y, 200 + X * (n + 1), 500); 
    settextstyle(1, 0, 3);
    if(point.value>=10){
    	outtextxy(200 + X * n+6 , 500 - point.value * Y - 30, itoa(point.value, buffer, 10));}
    	else
    outtextxy(200 + X * n + 16, 500 - point.value * Y - 30, itoa(point.value, buffer, 10));
}
//select
void selection(){
	for(int i = 0; i < sodinh - 1; i++) {
	    	int min=i;
	    	vediem(td[i],4,i);
	    	delay(700);
	        for (int j = i + 1; j < sodinh; j++) {
	        	if(td[j].value<td[min].value){
	        	xoadiem(td[min],15,min);
	        		min=j;
	        		vediem(td[i],4,i);
	        		vediem(td[j],5,j);
	        		delay(700);
				}}
			
			
				vediem(td[min],2,min);
				delay(400);
				cleardevice();
	                int tam = td[i].value;
	                td[i].value = td[min].value;
	                td[min].value = tam;
	                
	            vediem1(td,sodinh);
	         
	        }
	    
			vekhung();
			mouse();
	    for (int i = 0; i < sodinh; i++) {
	        todiem(td[i], 9, i);
	    }
	     enable_click=1;
	}
//bubble
void bubble(){
	for(int i=sodinh-1;i>0;i--){
		for(int k=0;k<i;k++){
		
			vediem1(td,sodinh);
			vediem2(td,sodinh,i);
			vediem(td[k+1],4,k+1);
			vediem(td[k],4,k);
			delay(400);
			if(td[k].value>td[k+1].value){
			cleardevice();
			int tam = td[k+1].value;
				td[k+1].value=td[k].value;
				td[k].value=tam;
				delay(10);
				vediem1(td,sodinh);
					vediem2(td,sodinh,i);
			vediem(td[k+1],9,k+1);
			vediem(td[k],9,k);
			delay(400);	
			}
			cleardevice();
			
		}
	}
		vekhung();
			mouse();
	for(int i=0;i<sodinh;i++)todiem(td[i],9,i);
	 enable_click=1;
}
//insert
void insertion(){
    for (int i = 1; i < sodinh; i++) {
        int j = i;
        vediem(td[i],4,i);
        while (j >= 0 && td[j].value <td[j-1].value ) {
       delay(500);
	   vediem(td[j-1],4,j-1);
	    vediem(td[j],4,j);       
        delay(200);
    	int tam=td[j].value;
          td[j].value=td[j-1].value;
          td[j-1].value=tam;
		  cleardevice();
	   		vediem1(td,sodinh); 
			vediem(td[j],2,j);
	    	vediem(td[j-1],2,j-1);
          j--;
        }
        delay(500);vediem1(td,sodinh);
        }
			vekhung();
			mouse();
    for (int i = 0; i < sodinh; i++) {
        todiem(td[i],9, i);
    }
     enable_click=1;
}
//phan hoach

void quickSortMidPivot(int left, int right) {
    if (left >= right) return;
    int mid = (right + left) / 2;
    int pivot = td[mid].value;
    cleardevice();
    vediem1(td, sodinh);          
    vediem(td[mid], 2, mid);      
    delay(500);
    int i = left;
    int j = right;
    while (i <= j) {
        while (td[i].value < pivot) i++;
        while (td[j].value > pivot) j--;
        if (i <= j) {
            int temp = td[i].value;
            td[i].value = td[j].value;
            td[j].value = temp;
            cleardevice();
            vediem1(td, sodinh);         
            vediem(td[mid], 2, mid);      
            vediem(td[i], 5, i);          
            vediem(td[j], 5, j);          
            delay(1000);

            i++;
            j--;
        }
    } 
    cleardevice();
    vediem1(td, sodinh);                 
    for (int k = left; k <= j; k++) {
        vediem(td[k], 4, k);              
    }
    for (int k = i; k <= right; k++) {
        vediem(td[k], 6, k);             
    }
    delay(1000);
    if (left < j) quickSortMidPivot(left, j);
    if (i < right) quickSortMidPivot(i, right);
}


	


int main(){

	setcolor(15);
	initwindow(1400,900);
	vekhung();
	mouse();
	getch();
	
}

