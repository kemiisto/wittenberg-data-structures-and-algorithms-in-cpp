#ifndef WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_LIST_H
#define WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_LIST_H

#include <initializer_list>

namespace wittenberg {
    template<typename T>
    class list {
    private:
        struct node {
            T data;
            node* rlink{nullptr};
            node* llink{nullptr};
            explicit node(const T& value = T{}) : data{value} {}
        };

        template <typename U>
        class iter {
        private:
            node* curr;
            friend class list<T>;
        public:
            explicit iter(node* p) : curr{p} {}
            U& operator*() const { return curr->data; }
            U* operator->() const { return &(curr->data); }
            bool operator==(const iter<U>& other) const { return curr == other.curr; }
            bool operator!=(const iter<U>& other) const { return curr != other.curr; }
            // prefix ++
            iter<U>& operator++() {
                curr = curr->rlink;
                return *this;
            }
            // postfix ++
            iter<U> operator++(int) {
                auto result = iter<U>(curr);
                curr = curr->rlink;
                return result;
            }
        };
    public:
        using iterator = iter<T>;
        using const_iterator = iter<const T>;

        list() : count{0}, first{nullptr}, last{nullptr} {}

        list(const list<T>& other) : list() {
            for (auto p = other.begin(); p != other.end(); p++) {
                push_back(*p);
            }
        }

        list(std::initializer_list<T> init) : list() {
            for (auto p = init.begin(); p != init.end(); p++) {
                push_back(*p);
            }
        }

        ~list() {
            while (first != nullptr) {
                auto* curr = first;
                first = first->rlink;
                delete curr;
            }
        }

        list<T>& operator=(const list<T>& other) {
            if (this != &other) {
                auto dest = begin();
                auto src = other.begin();
                // copy src elements into existing dest elements
                for (; dest != end() && src != other.end(); src++, dest++) {
                    *dest = *src;
                }
                // append excess src elements to this
                for (; src != other.end(); src++) {
                    push_back(*src);
                }
                // remove no longer needed nodes
                while (size() > other.size()) {
                    pop_back();
                }
            }
            return *this;
        }

        size_t size() const { return count; }
        bool empty() const { return size() == 0; }

        T& front() { return first->data; }
        const T& front() const { return first->data; }

        T& back() { return last->data; }
        const T& back() const { return last->data; }

        void push_front(const T& value) { insert(begin(), value); }
        void push_back(const T& value) { insert(end(), value); }
        void pop_front() { erase(begin()); }
        void pop_back() { erase(iterator(last)); }

        iterator insert(iterator pos, const T& value) {
            auto* new_node = new node(value);
            // link new_node to neighbor nodes
            new_node->rlink = pos.curr;
            if (pos.curr == nullptr) {
                new_node->llink = last;
            } else {
                new_node->llink = pos.curr->llink;
            }
            // link neighbor nodes to new_node
            if (new_node->rlink != nullptr) {
                new_node->rlink->llink = new_node;
            }
            if (new_node->llink != nullptr) {
                new_node->llink->rlink = new_node;
            }
            // adjust lat and fist, if necessary
            if (pos == begin()) { first = new_node; }
            if (pos == end()) { last = new_node; }

            ++count;
            return iterator(new_node);
        }

        iterator erase(iterator pos) {
            iterator result(pos.curr->rlink);
            // link left neighbor's rlink to right neighbor
            if (pos.curr = first) {
                first = first->rlink;
            } else {
                pos.curr->llink->rlink = pos.curr->rlink;
            }
            // link right neighbor's llink to left neighbor
            if (pos.curr = last) {
                last = last->llink;
            } else {
                pos.curr->rlink->llink = pos.curr->llink;
            }
            // make sure end pointers are null
            if (first != nullptr) {
                first->llink = last->rlink = nullptr;
            }
            delete pos.curr;
            --count;
            return result;
        }

        void clear() {
            // delete all of a list's nodes
            first = last = nullptr;
            count = 0;
        }

        iterator begin() { return iterator(first); }
        const_iterator begin() const { return const_iterator(first); }

        iterator end() { return iterator(nullptr); }
        const_iterator end() const { return const_iterator(nullptr); }
    private:
        // to keep track of the number of elements because the size function must be O(1)
        int count;
        node* first;
        node* last;
    };
}

#endif // WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_LIST_H
