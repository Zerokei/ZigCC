int printf(char *s, ...);
void *malloc(int __size);
void free(void *__ptr);

// 链表结点定义
struct ListNode {
    int val;
    struct ListNode *next;
};

// 链表头结点
struct ListNode *head;

// 创建链表结点
struct ListNode* createListNode(int val) {
    struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = 0;
    return node;
}

// 插入链表结点
void insertListNode(int val) {
    struct ListNode *node = createListNode(val);
    if (head == 0) {
        head = node;
    } else {
        struct ListNode *p = head;
        while (p->next != 0) {
            p = p->next;
        }
        p->next = node;
    }
}

// 删除链表结点
void deleteListNode(int val) {
    if (head == 0) {
        return;
    }
    if (head->val == val) {
        struct ListNode *p = head;
        head = head->next;
        free(p);
    } else {
        struct ListNode *p = head;
        while (p->next != 0 && p->next->val != val) {
            p = p->next;
        }
        if (p->next!= 0){
            struct ListNode *q = p->next;
            p->next = q->next;
            free(q);
        }
    }
}

// 查找链表结点
struct ListNode* findListNode(int val) {
    struct ListNode *p = head;
    while (p != 0 && p->val != val) {
        p = p->next;
    }
    return p;
}

// 打印链表
void printList() {
    struct ListNode *p = head;
    while (p != 0) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main() {
    head = 0;
    // 创建链表
    insertListNode(1);
    insertListNode(2);
    insertListNode(3);
    insertListNode(4);
    insertListNode(5);

    // 打印链表
    printf("链表初始状态：");
    printList();

    // 测试查找链表结点
    struct ListNode *node = findListNode(3);
    if (node != 0) {
        printf("查找链表结点 3 成功\n");
    } else {
        printf("查找链表结点 3 失败\n");
    }

    // 测试删除链表结点
    deleteListNode(4);
    printf("删除链表结点 4 后：");
    printList();

    // 测试插入链表结点
    insertListNode(6);
    printf("插入链表结点 6 后：");
    printList();

    // 释放链表内存
    struct ListNode *p = head;
    while (p != 0) {
        struct ListNode *q = p->next;
        free(p);
        p = q;
    }

    return 0;
}