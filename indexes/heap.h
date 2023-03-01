#pragma once

template<typename TK, typename TV>
class MaxHeap{
private:
    TV* trans;
    TK* arr;
    int capacity;
    int size;
public:

    MaxHeap(){
        arr = new TK[10];
        trans = new TV[10];
        this->size = 0;
        this->capacity = 10;
        this->size = size;
        buildHeap();
    }


    TV top(){
        std::cout<<"TOP VALUE: "<<std::endl;
        if(size>0){
            //std::cout<< arr[0] <<" && "<<trans[0]<<std::endl;
            return trans[0];
        }else{
            throw("No hay elementos");
        }
    }

    void insert(TK key, TV value)
    {
        // maintain same interface between DSs
        push(key,value);
    }

    void push(TK key, TV value){
        std::cout<<"Pushing KEY("<<key<<") with VALUE("<<value<<")"<<std::endl;
        if(size == capacity) resize();
        int index = size;
        arr[index] = key;
        trans[index] = value;
        //this->arr[index] = value;
        ++size;
        heapify_up(index);

    }
    void pop(){
        if(size == 0) return;
        swap(&arr[0], &arr[size-1]);
        swap2(&trans[0], &trans[size-1]);

        --size;
        heapify_down(0);
    }



private:
    void buildHeap(){
        for(int i=size/2; i>=0; --i){
            heapify_down(i);
        }
    }

    void swap(TK* xp, TK* yp){
        TK temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void swap2(TV* xp, TV* yp){
        TV temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    TK maxvalue(int index){
        TK max = index;
        if(left(index) >= right(index)){
            max = left(index);
        }
        return max;
    }

    TK minvalue(int index){
        TK min = index;
        if(left(index) <= right(index)){
            min = left(index);
        }
        return min;
    }

    int left(int index){
        return 2*index + 1;
    }
    int right(int index){
        return 2*index + 2;
    }
    int parent(int index){
        return (index-1) / 2;
    }
    void heapify_down(int parent){
        // Obtenemos hijo izquierdo e hijo derecho del indice
        int hijoizquierdo = left(parent);
        int hijoderecho = right(parent);

        int mayor = parent; //Inicializamos el valor mayor de ellos con el padre

        // Comparaciones para obtener el mayor valor de los hijos
        if (hijoizquierdo < size && arr[hijoizquierdo] > arr[parent]) {
            mayor = hijoizquierdo;
        }

        if (hijoderecho < size && arr[hijoderecho] > arr[mayor]) {
            mayor = hijoderecho;
        }

        // Swapeamos con el mayor
        if (mayor != parent)
        {
            swap(&arr[parent], &arr[mayor]);
            swap2(&trans[parent], &trans[mayor]);

            heapify_down(mayor);
        }
    }

    void heapify_up(int child){
        int padre = parent(child);
        if (arr[child] > arr[padre]) {
            swap(&arr[child], &arr[padre]);
            swap2(&trans[child], &trans[padre]);

            heapify_up(padre);
        }
    }

    void resize() {
        int nuevosize = size * 2;
        TK* newArr = new TK[nuevosize];
        TV* newArr2 = new TV[nuevosize];
        memcpy(newArr, arr, size * sizeof(int));
        memcpy(newArr2, trans, size * sizeof(int));

        size = nuevosize;
        delete[] arr;
        delete[] trans;
        arr = newArr;
        trans = newArr2;
        capacity = capacity*2;
    }
};

template<typename TK, typename TV>
class MinHeap{
private:
    TV* trans;
    TK* arr;
    int capacity;
    int size;
public:

    MinHeap(){
        arr = new TK[10];
        trans = new TV[10];
        this->size = 0;
        this->capacity = 10;
        this->size = size;
        buildHeap();
    }


    TV top(){
        std::cout<<"TOP VALUE: "<<std::endl;
        if(size>0){
            //std::cout<< arr[0] <<" && "<<trans[0]<<std::endl;
            return trans[0];
        }else{
            throw("No hay elementos");
        }
    }

    void insert(TK key, TV value)
    {
        // maintain same interface between DSs
        push(key,value);
    }

    void push(TK key, TV value){
        std::cout<<"Pushing KEY("<<key<<") with VALUE("<<value<<")"<<std::endl;
        if(size == capacity) resize();
        int index = size;
        arr[index] = key;
        trans[index] = value;
        //this->arr[index] = value;
        ++size;
        heapify_up(index);

    }
    void pop(){
        if(size == 0) return;
        swap(&arr[0], &arr[size-1]);
        swap2(&trans[0], &trans[size-1]);

        --size;
        heapify_down(0);
    }



private:
    void buildHeap(){
        for(int i=size/2; i>=0; --i){
            heapify_down(i);
        }
    }

    void swap(TK* xp, TK* yp){
        TK temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void swap2(TV* xp, TV* yp){
        TV temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    TK maxvalue(int index){
        TK max = index;
        if(left(index) >= right(index)){
            max = left(index);
        }
        return max;
    }

    TK minvalue(int index){
        TK min = index;
        if(left(index) <= right(index)){
            min = left(index);
        }
        return min;
    }

    int left(int index){
        return 2*index + 1;
    }
    int right(int index){
        return 2*index + 2;
    }
    int parent(int index){
        return (index-1) / 2;
    }
    void heapify_down(int parent){
        // Obtenemos hijo izquierdo e hijo derecho del indice
        int hijoizquierdo = left(parent);
        int hijoderecho = right(parent);

        int mayor = parent; //Inicializamos el valor mayor de ellos con el padre

        // Comparaciones para obtener el mayor valor de los hijos
        if (hijoizquierdo < size && arr[hijoizquierdo] < arr[parent]) {
            mayor = hijoizquierdo;
        }

        if (hijoderecho < size && arr[hijoderecho] < arr[mayor]) {
            mayor = hijoderecho;
        }

        // Swapeamos con el mayor
        if (mayor != parent)
        {
            swap(&arr[parent], &arr[mayor]);
            swap2(&trans[parent], &trans[mayor]);

            heapify_down(mayor);
        }
    }

    void heapify_up(int child){
        int padre = parent(child);
        if (arr[child] < arr[padre]) {
            swap(&arr[child], &arr[padre]);
            swap2(&trans[child], &trans[padre]);

            heapify_up(padre);
        }
    }

    void resize() {
        int nuevosize = size * 2;
        TK* newArr = new TK[nuevosize];
        TV* newArr2 = new TV[nuevosize];
        memcpy(newArr, arr, size * sizeof(int));
        memcpy(newArr2, trans, size * sizeof(int));

        size = nuevosize;
        delete[] arr;
        delete[] trans;
        arr = newArr;
        trans = newArr2;
        capacity = capacity*2;
    }
};