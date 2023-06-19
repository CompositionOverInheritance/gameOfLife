#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>


using namespace std;

const int dim = 20;


class Cell {
  public:
    bool alive;
    bool nextState;
    int posX;
    int posY;

    static Cell* cellArray[dim][dim];
 
    Cell(){
      this->alive = false;
      this->nextState = false;
    }
 
    Cell(int x, int y){
      this->alive = false;
      this->nextState = false;
      this->posX = x;
      this->posY = y;
    }

    void tick(){
      this->alive = this->nextState;
    }

    // set nextState variable, which is used durin tick(update)
    void setNextState(){
      int neighbors = this->checkNeighbors();
      if(this->alive){ 
        if(neighbors < 2){
          this->nextState = false;
        }else if(neighbors > 3){
          this->nextState = false;
        }else if((neighbors == 2) || (neighbors == 3)){
          this->nextState = true;
        }
      }else{
        if(neighbors == 3){
          this->nextState = true;
        }
      }
    } // end of setNextState
    
    // return the number of living neighbors
    int checkNeighbors(){
      int neighborCount = 0;
      for(int i = 0; i < 8; i++){
        // first check whether givend position is valid
        // if it is then check if it's alive
        switch (i) {
          case 0:
            if( ((this->posX + 1) >= dim) && (this->posY >= 0) && (this->posY < dim) ){
            }else{ if( Cell::cellArray[this->posY][this->posX+1]->alive){ neighborCount++; }}
            break; 
          case 1:
            if( ((this->posY + 1) >= dim) && (this->posX >= 0) && (this->posX < dim) ){
            }else{ if( Cell::cellArray[this->posY+1][this->posX]->alive){ neighborCount++; }}
            break; 
          case 2:
            if( ((this->posX + 1) >= dim) || ((this->posY + 1) >= dim) ){
            }else{ if( Cell::cellArray[this->posY+1][this->posX+1]->alive){ neighborCount++; }}
            break; 
          case 3:
            if( ((this->posX - 1) < 0) || ((this->posY + 1) >= dim) ){
            }else{ if( Cell::cellArray[this->posY+1][this->posX-1]->alive){ neighborCount++; }}
            break; 
          case 4:
            if( ((this->posX + 1) >= dim) || ((this->posY - 1) < 0) ){
            }else{ if( Cell::cellArray[this->posY-1][this->posX+1]->alive){ neighborCount++; }}
            break; 
          case 5:
            if( ((this->posX - 1) < 0) || ((this->posY - 1) < 0) ){
            }else{ if( Cell::cellArray[this->posY-1][this->posX-1]->alive){ neighborCount++; }}
            break; 
          case 6:
            if( ((this->posX - 1) < 0) && (this->posY >= 0) && (this->posY < dim) ){
            }else{ if( Cell::cellArray[this->posY][this->posX-1]->alive){ neighborCount++; }}
            break; 
          case 7:
            if( ((this->posY - 1) < 0) && (this->posX >= 0) && (this->posX < dim) ){
            }else{ if( Cell::cellArray[this->posY-1][this->posX]->alive){ neighborCount++; }}
            break;
          default:
            break;
        } // end of switch
      } // end of for loop 
      return neighborCount; 
    } // end of checkNeighbors

    friend ostream& operator<<(ostream& os, const Cell& cell);

}; // end of Class Cell definition

// display living and dead cells as custom characters
ostream& operator<<(ostream& os, const Cell& cell){
  ostringstream oss;

  if(cell.alive){
    oss << "O"; 
  }else{
    oss << ".";
  }

  return os << oss.str();
}

Cell* Cell::cellArray[dim][dim];

int main(){

  bool seedArray[dim][dim] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };


  Cell cellArr[dim][dim];


  cout << "initial screen with the seed" << endl;
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      cellArr[i][j] = Cell(j,i);
      cellArr[i][j].alive = seedArray[i][j];
    }
    cout << endl;
  }


  cout << "displaying the initial screen" << endl;
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      cout << cellArr[i][j] << " ";
    }
    cout << endl;
  }



  // assigning the local cellArr to the static member cellArray
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      Cell::cellArray[i][j] = &cellArr[i][j];
    }
  }



while(true){

  // set next state
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      cellArr[i][j].setNextState(); 
    }
  }

  // tick
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      cellArr[i][j].tick(); 
    }
  }

  cout << "==========FRAME==========" << endl;
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      cout << *(Cell::cellArray[i][j]) << " ";
    }
    cout << endl;
  }
  cout << "=========================" << endl;

  sleep(1);
} // end of while update loop


  return 0;
}
