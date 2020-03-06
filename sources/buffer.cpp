#include "buffer.hpp"

Buffer::Buffer(int capacity_){
  cells.resize(static_cast<size_t>(capacity_));

  int number = 1;
  for(auto &cell: cells) {
    cell.setNumber(number);
    ++number;
  }
  stepts = nullptr;
  ringIterator = cells.begin();
}

Buffer::~Buffer(){
    cells.clear();
}

bool Buffer::empty(){
    for(auto &cell : cells) {
        if(!cell.isEmpty()) {
            return false;
        }
    }
    return true;
}

void Buffer::setStatistics(std::vector<Step > *steps){
    this->stepts = steps;
}

void Buffer::addRequest(Request &request){
    for(auto &cell : cells) {
        if(cell.isEmpty()) {
            //std::cout << "Положили заявку в ячейку: " << cell.getNumber()
             //         << " заявка от: " << request.getGenerator()->getProductionNumber()
              //        << " источника со временем: " << request.getGeneratedTime() << std::endl;
            if(stepts != nullptr) {
                stepts->push_back({1,cell.getNumber(), request.getGenerator()->getProductionNumber(), request.getGeneratedTime(),0});

            }

            cell.setRequest(request);
            cell.setEmpty(false);
            tmpCell = &cell;
            break;
        }
    }
}

bool Buffer::hasEmptyCell() {
    for(auto &cell : cells) {
        if(cell.isEmpty()) {
            //std::cout << "Свободная ячейка: " << cell.getNumber() << std::endl;
            return true;
        }
    }
    //std::cout<< "Буфер забит" << std::endl;
    return false;
}

void Buffer::rejectRequest() {
    //Взять из буфера заявку с наименьшем временем, и положить текущую
    BuffIterator minIt = std::max_element(cells.begin(), cells.end(), [](Cell &cell1, Cell &cell2) {
        return cell1.getRequest()->getGeneratedTime() < cell2.getRequest()->getGeneratedTime();
    });
    //Индекс на этот итератор
    index = static_cast<unsigned long>(std::distance(cells.begin(), minIt));
    cells.at(index).getRequest()->getGenerator()->setCountOfRejectedApplications(1);
    tmpCell = &cells.at(index);
}

void Buffer::replaceRejected(Request &request){
    cells.at(index).setRequest(request);
    if(stepts != nullptr) {
        stepts->push_back({1,cells.at(index).getNumber(), request.getGenerator()->getProductionNumber(), request.getGeneratedTime(),0});
    }
    tmpCell = &cells.at(index);
}

bool Buffer::getAllCells(){
    if(tmpRinfIterator == ringIterator){
       return true;
    }
    return false;
}

void Buffer::setStartIter(){
    tmpRinfIterator = ringIterator;
}

Cell& Buffer::getRequestWithPriority() {

    for(BuffIterator cell = ringIterator; cell != cells.end(); ++cell){
        if(!cell->isEmpty()){
            ringIterator = cell;
            increaseBuffIterator();
            return *cell;
        }
    }

    for(BuffIterator cell = cells.begin(); cell != ringIterator; ++cell){
        if(!cell->isEmpty()){
            ringIterator = cell;
            increaseBuffIterator();
            return *cell;
        }
    }
}

void Buffer::increaseBuffIterator(){
    ringIterator->getNumber() == cells.size() ? ringIterator = cells.begin() : ++ringIterator;
}

BuffIterator& Buffer::getRingIterator(){
    return ringIterator;
}



