#include "geesespotter_lib.h"
#include "geesespotter.h"

char * createBoard(std::size_t xdim, std::size_t ydim){
    char * board = new char[xdim*ydim];
    for (int i = 0; i < xdim*ydim; i++){
        board[i]=0;
    }
    
    // for (int i = 0; i < xdim*ydim*sizeof(char); i++){
    //     *(board+i*sizeof(char)) = 0;
    // }
    return board;
}
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    
    for(int l = 0; l < ydim; l++){
        for(int r = 0; r < xdim; r++){
        int a = 0;
        //same lime (l*xidm+r)<((l+1)*xdim)&&(l*xdim+r)>=(l*xdim)
        if(board[l*xdim+r]!=9){
            if((((l*xdim+r)-xdim)<=xdim*ydim)&&((l*xdim+r)-xdim>=0)){
                if((board[l*xdim+r-xdim]&valueMask()) == 9){
                    //if((yloc*xdim+xloc-xdim)>0)
                a++;}
            }
            if((((l*xdim+r)-xdim+1)<=xdim*ydim)&&((l*xdim+r)-xdim+1>=0)&&(((l*xdim+r)+1-xdim)<(l*xdim))){
                //if(((yloc*xdim+xloc+1-xdim)>0)&&((yloc*xdim+xloc+1-xdim)<(yloc*xdim))&&((yloc*xdim+xloc+1-xdim)<=xdim*ydim)))
                if((board[l*xdim+r-xdim+1]&valueMask())==9){
                    a++;
                }
            }
            if((((l*xdim+r)-xdim-1)<=xdim*ydim)&&((l*xdim+r)-xdim-1>=0)&&((l*xdim+r-1-xdim)>=(l*xdim-xdim))){
                //if(((yloc*xdim+xloc-1-xdim)>0)&&((yloc*xdim+xloc-1-xdim)<(xdim*ydim))&&((yloc*xdim+xloc-1-xdim)>=(yloc*xdim-xdim)))
                if ((board[l*xdim+r-xdim-1]&valueMask())==9){
                    a++;
                }
            }
            if(((l*xdim+r-1)<=xdim*ydim)&&((l*xdim+r-1)>=0)&&((l*xdim+r-1)>=(l*xdim))){
                //if(((yloc*xdim+xloc-1)>0)&&((yloc*xdim+xloc-1)>=(yloc*xdim)))
                if ((board[l*xdim+r-1]&valueMask())==9){
                    a++;
                }
            }
            if(((l*xdim+r+1)<=xdim*ydim)&&((l*xdim+r+1)<(l*xdim+xdim))){
                // if((yloc*xdim+xloc+1>0)&&((yloc*xdim+xloc+1)<(xdim*ydim))&&((yloc*xdim+xloc+1)<(yloc*xdim+xdim)))

                if ((board[l*xdim+r+1]&valueMask())==9){
                    a++;
                }
            }
            if((l*xdim+r)+xdim<=xdim*ydim){
                //if(((yloc*xdim+xloc+xdim)>0)&&((yloc*xdim+xloc+xdim)<(xdim*ydim)))
                if((board[l*xdim+r+xdim]&valueMask())==9){
                    a++;
                    }
            }
            if((((l*xdim+r)+xdim+1)<=xdim*ydim)&&((l*xdim+r+1+xdim)<(l*xdim+2*xdim))){
                //if(((yloc*xdim+xloc+1+xdim)>0)&&((yloc*xdim+xloc+1+xdim)<(xdim*ydim))&&((yloc*xdim+xloc+1+xdim)<(yloc*xdim+2*xdim)))
                
                if((board[l*xdim+r+xdim+1]&valueMask())==9){
                    a++;
                }
            }
            if((((l*xdim+r)+xdim-1)<=xdim*ydim)&&((l*xdim+r-1+xdim)>=(l*xdim+xdim))){
                //if(((yloc*xdim+xloc-1+xdim)>0)&&((yloc*xdim+xloc-1+xdim)<(xdim*ydim))&&((yloc*xdim+xloc-1+xdim)>=(yloc*xdim+xdim)))
                if((board[l*xdim+r+xdim-1]&valueMask())==9){
                    a++;
                }
            }
            board[l*xdim+r]=(board[l*xdim+r]&valueMask());
            board[l*xdim+r]|=a;
        }
        
        if(board[l*xdim+r]==9){
                board[l*xdim+r]=(board[l*xdim+r]&valueMask());
                
        }
        
        }
        
    }
}
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int o = 0; o < xdim*ydim; o++){
        board[o]|=hiddenBit();
    }
}
void cleanBoard(char * board){
    delete[] board;
    board = NULL;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    int p = 0;
    int k = 1;
    for (int i = 0; i < ydim; i++){
        
        for(int y = 0; y < xdim; y++){
            
            if((board[y+i*xdim]&markedBit())==markedBit()){
                std::cout<<"M";
            }
            else if ((board[y+i*xdim]&hiddenBit())==hiddenBit()){
                std::cout<<"*";
                }
            else{
                std::cout<<(board[y+i*xdim]&valueMask());
                }
            }
        std::cout<<"\n";    
        }
        
        
    }

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
        
        if((board[yloc*xdim+xloc]&markedBit())==markedBit()){
            return 1;
        }
        else if ((board[yloc*xdim+xloc]&hiddenBit())!=hiddenBit()){
            return 2;
        }
        else if ((board[yloc*xdim+xloc]&valueMask())==9){
            board[yloc*xdim+xloc]&=(~hiddenBit());
            return 9;
        }
        else{
            if((board[yloc*xdim+xloc]&valueMask())==0){
                board[yloc*xdim+xloc]&=(~hiddenBit());
            if((yloc*xdim+xloc+1>0)&&((yloc*xdim+xloc+1)<=(xdim*ydim))&&((yloc*xdim+xloc+1)<(yloc*xdim+xdim))){
                board[yloc*xdim+xloc+1]&=(~hiddenBit());
            }
            if(((yloc*xdim+xloc-1)>=0)&&((yloc*xdim+xloc-1)>=(yloc*xdim))){
                board[yloc*xdim+xloc-1]&=(~hiddenBit());
            }
            if(((yloc*xdim+xloc+1+xdim)>0)&&((yloc*xdim+xloc+1+xdim)<=(xdim*ydim))&&((yloc*xdim+xloc+1+xdim)<(yloc*xdim+2*xdim))){
                board[yloc*xdim+xloc+1+xdim]&=(~hiddenBit());
            }
            if(((yloc*xdim+xloc-1+xdim)>0)&&((yloc*xdim+xloc-1+xdim)<=(xdim*ydim))&&((yloc*xdim+xloc-1+xdim)>=(yloc*xdim+xdim))){
                board[yloc*xdim+xloc-1+xdim]&=(~hiddenBit());
            }
            if(((yloc*xdim+xloc+xdim)>0)&&((yloc*xdim+xloc+xdim)<=(xdim*ydim))){
                board[yloc*xdim+xloc+xdim]&=(~hiddenBit());
            }
            if(((yloc*xdim+xloc-1-xdim)>=0)&&((yloc*xdim+xloc-1-xdim)<=(xdim*ydim))&&((yloc*xdim+xloc-1-xdim)>=(yloc*xdim-xdim))){
                board[yloc*xdim+xloc-1-xdim]&=(~hiddenBit()); 
            }
            if(((yloc*xdim+xloc+1-xdim)>=0)&&((yloc*xdim+xloc+1-xdim)<(yloc*xdim))&&((yloc*xdim+xloc+1-xdim)<=(xdim*ydim))){
                board[yloc*xdim+xloc+1-xdim]&=(~hiddenBit());
            }
            if((yloc*xdim+xloc-xdim)>=0){
                board[yloc*xdim+xloc-xdim]&=(~hiddenBit());
            }
        }
            else{
                board[yloc*xdim+xloc]&=(~hiddenBit());
            }
        }
        
    
    return 0;
}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    if((board[yloc*xdim+xloc]&hiddenBit())!=hiddenBit()){
        return 2;
    }
    
    else{
        board[yloc*xdim+xloc]^=markedBit();
        return 0;
        }
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    int a = 0;
    int c = 0;
    //know how many numbers are geeses
    //know how many numbers are revealed
    for (int w = 0; w< xdim*ydim; w++){
        if (((board[w]&hiddenBit())==0)&&((board[w]&valueMask())!=9)){
            c++;
        }
        else if ((board[w]&valueMask())==9){
            a++;
        }
    }
        // std::cout<<"c "<<c;
        // std::cout<<" a "<<a;
        if (c == (xdim*ydim-a)){
            return true;
        }
        else{
            return false;
        }
}

