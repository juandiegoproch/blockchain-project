#pragma once

template<typename T>
class SinglyLinkedList
{
    struct Node
    {
        T data;
        Node* next;

        Node(const T data_, Node* next_ = nullptr)
        {
            data = data_;
            next = next_;
        }

        void killFolowing()
        {
            // todos los nodos se crean en heap
            if (next != nullptr)
            {
                next->killFolowing();
                delete next;
            }
        }

        ~Node()
        {
        }
    };

private:
    Node* head;

public:
    SinglyLinkedList()
    {
        head = nullptr;
    }

    void push_back(const T dato)
    {
        // caso lista vacia
        if (head == nullptr)
            head = new Node(dato,nullptr);


        Node* traverser = head;
        // avanzame hasta el final!
        while (traverser->next != nullptr) traverser = traverser->next;

        traverser->next = new Node(dato);
    }

    void insert(T dato,unsigned int index)
    {
        // caso lista vacia
        if (head == nullptr)
        {
            throw ("Index Out Of Bounds");
            return;
        }
        // en caso se inserte el el frente
        if (index == 0)
        {
            head = new Node(dato, head);
        }

        //ir a donde tengo que ir
        Node* traverser = head;
        //                 index - 1
        //                 index - 1 porque necesito el ANTERIOR a la poscicion en la que deseo insertar
        for(int i = 0; i < index - 1;i++)
        {
            if (traverser->next == nullptr)
            {
                // caso fin de la lista
                throw("Index Out Of Bounds");
                return;
            }

            traverser = traverser->next;
        }

        //insertar las cosas
        Node* tmp = traverser->next;
        traverser->next = new Node(dato,tmp);
    }

    void push_front(T dato)
    {
        head = new Node(dato,head);
    }

    empty()
    {
        return head == nullptr;
    }

    T pop_front()
    {
        if (head == nullptr)
        {
            throw("Out Of Bounds");
            return T();
        }

        Node* init = head;
        head = head->next;

        init->next = nullptr;
        T dato = init->data;

        delete init;

        return dato;


    }

    T pop_back()
    {
        // caso lista vacia
        if (head == nullptr)
            throw "invalid pop on empty list";


        Node* traverser = head;
        // avanzame hasta el final!
        while (traverser->next->next != nullptr) traverser = traverser->next;

        Node* end = traverser->next;
        traverser->next = nullptr;

        T dato = end->data;
        delete end;
        return dato;
    }



    ~SinglyLinkedList()
    {
        // por recursividad todos se eliminan. En caso nullptr nada pasa
        if (head != nullptr)
        {
            head->killFolowing();
            delete head;
        }
    }

};