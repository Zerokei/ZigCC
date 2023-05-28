int printf(char *s, ...);

// 定义链表节点
struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head; // 链表头指针

public:
    LinkedList() {
        head = 0;
    }

    // 在链表头插入节点
    void insertAtBeginning(int element) {
        Node* newNode = new Node();
        newNode->data = element;
        newNode->next = head;
        head = newNode;
    }

    // 在链表尾插入节点
    void insertAtEnd(int element) {
        Node* newNode = new Node();
        newNode->data = element;
        newNode->next = 0;
        if (head == 0) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != 0) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // 删除指定元素
    void deleteElement(int element) {
        if (head == 0) {
            printf("链表为空\n");
            return;
        }
        Node* temp = head;
        Node* prev = 0;
        while (temp != 0 && temp->data != element) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == 0) {
            printf("元素不存在\n");
            return;
        }
        if (prev == 0) {
            head = temp->next;
        }
        else {
            prev->next = temp->next;
        }
        delete temp;
    }

    // 修改指定元素的值
    void updateElement(int oldElement, int newElement) {
        if (head == 0) {
            printf("链表为空\n");
            return;
        }
        Node* temp = head;
        while (temp != 0 && temp->data != oldElement) {
            temp = temp->next;
        }
        if (temp == 0) {
            printf("元素不存在\n");
            return;
        }
        temp->data = newElement;
    }

    // 查找指定元素
    void findElement(int element) {
        if (head == 0) {
            printf("链表为空\n");
            return;
        }
        Node* temp = head;
        while (temp != 0 && temp->data != element) {
            temp = temp->next;
        }
        if (temp == 0) {
            printf("元素不存在\n");
            return;
        }
        printf("元素 %d 存在链表中", element);
    }

    // 打印链表
    void printList() {
        if (head == 0) {
            printf("链表为空\n");
            return;
        }
        Node* temp = head;
        while (temp != 0) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
};

int main() {
    LinkedList list;
    list.insertAtBeginning(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);
    list.printList(); // 5 10 20 30
    list.deleteElement(20);
    list.printList(); // 5 10 30
    list.updateElement(10, 15);
    list.printList(); // 5 15 30
    list.findElement(30); // 元素 30 存在于链表中
    return 0;
}