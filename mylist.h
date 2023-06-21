#pragma once

#include <iostream>
#include <limits>
#include <fstream>



// шаблонный класс лист. содержит 2 вложенных класса Node с данными, и Iterator (для итерирования по листу)
template <typename T>
class List {
    class Node;

public: //функции с других библиотек которые  могут работать с моим классом (общепринятые тайпдефы)
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    class ListIterator {
        // содержит ноду в приватном поле а также перегруженные операторы ++ -- * == !=
        // ++ -- операторы инкремента и декримента, чтобы перемещаться по листу
        // * оператор разыменования
    public:
        ListIterator() : current_node_(nullptr) {}
        explicit ListIterator(Node* ptr_node) : current_node_(ptr_node) {}

        Node* GetCurrentNode() { return current_node_; }
        ListIterator& operator++() {
            current_node_ = current_node_->next_node_;
            return *this;
        }

        ListIterator& operator--() {
            current_node_ = current_node_->prev_node_;
            return *this;
        }

        const_reference operator*() { return current_node_->node_data_; }

        bool operator==(const ListIterator& other) {
            return this->current_node_ == other.current_node_;
        }

        bool operator!=(const ListIterator& other) {
            return this->current_node_ != other.current_node_;
        }

    private:
        Node* current_node_;
    };

    typedef ListIterator iterator;
    typedef const ListIterator const_iterator;

public:
    // конструкторы
    List();
    explicit List(size_type n);
    explicit List(std::initializer_list<value_type> const& items);
    List(const List& l);
    List(List&& l);
    ~List();
    // перегрузка операторов =
    List& operator=(const List& l);
    List& operator=(List&& l);

public:
    // бегин енд - бегин возвращает обьект итератора на первый элемент, чтобы получить значение из него его нужно разыменовать *
    // енд возвращает обьект итератора указывающего на элемент за последним (афтер тейл)
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // получить первый и последний элементы списка
    const_reference front();
    const_reference back();
    // проверка на пустой список
    bool empty() const noexcept;
    // возвращает размер списка
    size_type size() const noexcept;
    // очистка списка
    void clear();
    iterator insert(iterator pos, const_reference value);
    // найти элемент, возвращает итератор, внутри содержится нода с данными(если ничего нет в ноде лежит нуллпоинтер)
    iterator find(const_reference value);
    // найти минимум, возвращает значение
    value_type find_min();
    // удалить элемент. принимает итератор. то есть к примеру список {5, 8, 9, 2, 9} чтобы удалить первое вхождение 9
    // сначала применяет функцию ''auto elem = find(9)'' а затем этот elem запихиваем в аргумент erase
    void erase(iterator pos);
    // пуш бэк/фронт и поп бэк/фронт удаляет или добавляет элемент в конец или начало
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    // функция меняет местами содержимое списков.
    // noexcept говорит компилятору чтобы эта функция не бросила исключения ,оптимизируя работу
    void swap(List& other) noexcept;
    // сортирует список. сортировка методом вставки
    void sort();

public:
    // функции экспорта и импорта принимают или путь к файлу или названия файла
    void list_import(std::string path);
    void list_export(std::string file_name);

public:
    // выводит содержимое листа в терминал
    void print_from_head();

private:
    // приватный класс ноде, содежит данные. также каждая нода содежит указатель на предыдущий элемент, на следующий элемент
    // в конструкторе по умолчанию нода инициализируется нулпоинтерми
    class Node {
    public:
        value_type node_data_;
        Node* prev_node_;
        Node* next_node_;
        Node() : node_data_(), prev_node_(nullptr), next_node_(nullptr) {}

    };
    //указатели на первый и последний элемент. эти указатели уже содержатся в основном классе List
    Node* Head_;
    Node* Tail_;
    // афтертейл указатель на ноду которая идет за последней. нужен для итератора
    Node* After_Tail_;

    // две приватные функции которые вызываются из основных функций. сделаны для читаемости кода
    void PushBack(Node* temp);
    void PushFront(Node* temp);
};

// дальше идет вынесенный код каждой функции по отдельности

template <typename value_type>
List<value_type>::List() : Head_(nullptr), Tail_(nullptr) {
    After_Tail_ = new Node;
}

template <typename value_type>
List<value_type>::List(size_type n) : List() {
    if (n) {
        for (size_type i = 0; i < n; ++i) {
            Node* temp(new Node);
            PushBack(temp);
        }
    }
}

template <typename value_type>
List<value_type>::List(std::initializer_list<value_type> const& items)
        : List() {
    for (auto element : items) {
        push_back(element);
    }
}

template <typename value_type>
List<value_type>::List(const List& l) : List() {
    *this = l;
}

template <typename value_type>
List<value_type>::List(List&& l) : List() {
    *this = std::move(l);
}

template <typename value_type>
List<value_type>::~List() {
    clear();
    delete After_Tail_;
    After_Tail_ = nullptr;
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(const List& l) {
    if (this == &l) throw std::out_of_range("Coping the same list is forbidden!");
    clear();
    for (auto it = l.cbegin(); it != l.cend(); ++it) this->push_back(*it);
    return *this;
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(List&& l) {
    this->swap(l);
    l.clear();
    return *this;
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::begin() noexcept {
    if (Head_)
        return iterator(Head_);
    else
        return iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::end() noexcept {
    return iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::cbegin()
const noexcept {
    if (Head_)
        return const_iterator(Head_);
    else
        return const_iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::cend()
const noexcept {
    return const_iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::front() {
    if (!size()) throw std::out_of_range("List is empty!");
    iterator first_node = begin();
    return *first_node;
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::back() {
    if (!size()) throw std::out_of_range("List is empty!");
    iterator last_node = end();
    --last_node;
    return *last_node;
}

template <typename value_type>
bool List<value_type>::empty() const noexcept {
    return (Head_ == nullptr && Tail_ == nullptr);
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::size() const noexcept {
    size_type count = 0;
    for (auto it = cbegin(); it != cend(); ++it) ++count;
    return count;
}

template <typename value_type>
void List<value_type>::clear() {
    while (empty() == false) pop_front();
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::insert(
        iterator pos, const_reference value) {
    Node* pos_node = pos.GetCurrentNode();
    iterator inserted_pos;
    if (pos_node == Head_ || empty() == true) {
        push_front(value);
        inserted_pos = begin();
    } else {
        --pos;
        Node* previous_node = pos.GetCurrentNode();
        Node* inserted_node(new Node);
        inserted_node->node_data_ = value;
        inserted_node->next_node_ = pos_node;
        inserted_node->prev_node_ = previous_node;
        pos_node->prev_node_ = inserted_node;
        previous_node->next_node_ = inserted_node;
        iterator inserted_pos_tmp(inserted_node);
        inserted_pos = inserted_pos_tmp;
    }
    return inserted_pos;
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::find(const_reference value) {
    auto result = begin();
    while(result.GetCurrentNode() != After_Tail_) {
        if(*result == value) {
            return result;
        }
        ++result;
    }
    return iterator(nullptr);
}

template <typename value_type>
value_type List<value_type>::find_min() {
    auto needle = begin();
    auto result = needle;
    while(needle.GetCurrentNode() != After_Tail_) {
        if(*needle < *result) {
            result = needle;
        }
        ++needle;
    }
    return *result;
}

template <typename value_type>
void List<value_type>::erase(iterator pos) {
    if (empty() == true)// возвращает булевое значение true если список пуст
        throw std::out_of_range("List is empty! Nothing to be erased");
    Node* pos_node = pos.GetCurrentNode();
    if (pos_node == After_Tail_)
        throw std::out_of_range("The past-the-last element cannot be erased.");
    if (pos_node == Head_) {
        pop_front();
    } else if (pos_node == Tail_) {
        pop_back();
    } else {
        --pos;
        Node* previous_node = pos.GetCurrentNode();
        previous_node->next_node_ = pos_node->next_node_;
        (pos_node->next_node_)->prev_node_ = previous_node;
        delete pos_node;
        pos_node = nullptr;
    }
}

template <typename value_type>
void List<value_type>::push_back(const_reference value) {
    Node* temp(new Node);
    temp->node_data_ = value;
    PushBack(temp);
}

template <typename value_type>
void List<value_type>::push_front(const_reference value) {
    Node* temp(new Node);
    temp->node_data_ = value;
    PushFront(temp);
}

template <typename value_type>
void List<value_type>::pop_back() {
    if (!size()) throw std::out_of_range("List is empty!Pop_back is impossible");
    Node* temp = nullptr;
    temp = Tail_;
    if (size() == 1) {
        Head_ = nullptr;
        Tail_ = nullptr;
    } else {
        Tail_ = temp->prev_node_;
        Tail_->next_node_ = After_Tail_;
    }
    delete temp;
    temp = nullptr;
}

template <typename value_type>
void List<value_type>::pop_front() {
    if (!size()) throw std::out_of_range("List is empty!Pop_back is impossible");
    Node* temp = nullptr;
    temp = Head_;
    if (size() == 1) {
        Head_ = nullptr;
        Tail_ = nullptr;
    } else {
        Head_ = temp->next_node_;
        Head_->prev_node_ = After_Tail_;
        After_Tail_->next_node_ = Head_;
    }
    delete temp;
    temp = nullptr;
}

template <typename value_type>
void List<value_type>::swap(List& other) noexcept {
    if (this != &other) {
        std::swap(this->Head_, other.Head_);
        std::swap(this->Tail_, other.Tail_);
        std::swap(this->After_Tail_, other.After_Tail_);
    }
}

template <typename value_type>
void List<value_type>::sort() {
    if (empty() == false) {
        iterator it_end = cend();
        iterator it_last_element = --it_end;
        ++it_end;
        for (auto it = cbegin(); it != it_end; ++it) {
            for (auto it2 = cbegin(); it2 != it_last_element;) {
                value_type current_element = *it2;
                Node* current_point_to_node = it2.GetCurrentNode();
                value_type next_element = *(++it2);
                Node* next_point_to_node = it2.GetCurrentNode();
                if (current_element > next_element && next_point_to_node != After_Tail_)
                    std::swap(current_point_to_node->node_data_,
                              next_point_to_node->node_data_);
            }
        }
    }
}

template <typename value_type>
void List<value_type>::print_from_head() {
    Node* temp = nullptr;
    temp = Head_;
    while (temp != After_Tail_ && temp) {
        std::cout << temp->node_data_ << "\n";
        temp = temp->next_node_;
    }
}

template <typename value_type>
void List<value_type>::PushBack(Node* temp) {
    temp->next_node_ = After_Tail_;
    After_Tail_->prev_node_ = temp;
    if (Head_) {
        temp->prev_node_ = Tail_;
        Tail_->next_node_ = temp;
        Tail_ = temp;
    } else {
        temp->prev_node_ = After_Tail_;
        Head_ = temp;
        Tail_ = temp;
    }
    After_Tail_->next_node_ = Head_;
}

template <typename value_type>
void List<value_type>::PushFront(Node* temp) {
    temp->prev_node_ = After_Tail_;
    After_Tail_->next_node_ = temp;
    if (Head_) {
        temp->next_node_ = Head_;
        Head_->prev_node_ = temp;
        Head_ = temp;
    } else {
        temp->next_node_ = After_Tail_;
        Head_ = temp;
        Tail_ = temp;
    }
    After_Tail_->prev_node_ = Tail_;
}

template <typename value_type>
void List<value_type>::list_export(std::string file_name) {
    std::ofstream file;
    file.open(file_name);
    if (file.is_open()){
        for(auto &el: *this) file << el << "\n";
    } else {
        std::cout << "can't open file" << std::endl;
    }
    file.close();
}


template <typename value_type>
void List<value_type>::list_import(std::string path) {
    std::ifstream file;
    file.open(path);
    if (file.is_open()){
        this->clear();
        std::string line;
        while(getline(file, line)) {
            this->push_back(line);
        }
    } else {
        std::cout << "can't open file" << std::endl;
    }
    file.close();
}

