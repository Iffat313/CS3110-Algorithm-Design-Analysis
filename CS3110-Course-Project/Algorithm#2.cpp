#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge {
    string dest;
    int weight;
    Edge* next;
};

struct Vertex {
    string name;
    Edge* head;
};

void addEdge(Vertex& v, string dest, int weight) {
    Edge* e = new Edge();
    e->dest = dest;
    e->weight = weight;
    e->next = NULL;

    if (v.head == NULL) {
        v.head = e;
        return;
    }

    Edge* curr = v.head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = e;
}

void splitList(Edge* source, Edge** front, Edge** back) {
    Edge* slow = source;
    Edge* fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Edge* merge(Edge* a, Edge* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->dest < b->dest) {
        a->next = merge(a->next, b);
        return a;
    }

    b->next = merge(a, b->next);
    return b;
}

Edge* mergeSort(Edge* head) {
    if (head == NULL || head->next == NULL)
        return head;

    Edge* front;
    Edge* back;
    splitList(head, &front, &back);

    front = mergeSort(front);
    back  = mergeSort(back);

    return merge(front, back);
}

void printList(vector<Vertex>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << graph[i].name;
        Edge* curr = graph[i].head;
        while (curr != NULL) {
            cout << " -> (" << curr->dest << ", " << curr->weight << ")";
            curr = curr->next;
        }
        cout << endl;
    }
}

int main() {
    vector<Vertex> graph(5);
    graph[0].name = "A"; graph[0].head = NULL;
    graph[1].name = "B"; graph[1].head = NULL;
    graph[2].name = "C"; graph[2].head = NULL;
    graph[3].name = "D"; graph[3].head = NULL;
    graph[4].name = "E"; graph[4].head = NULL;

    addEdge(graph[0], "E", 16);
    addEdge(graph[0], "C", 14);
    addEdge(graph[0], "B", 18);
    addEdge(graph[1], "D", 10);
    addEdge(graph[1], "C", 2);
    addEdge(graph[2], "E", 6);
    addEdge(graph[2], "B", 13);
    addEdge(graph[2], "A", 5);
    addEdge(graph[3], "E", 11);
    addEdge(graph[3], "C", 15);
    addEdge(graph[3], "B", 19);
    addEdge(graph[3], "A", 3);
    addEdge(graph[4], "D", 8);
    addEdge(graph[4], "C", 17);

    cout << "Before the sort:" << endl;
    printList(graph);

    for (int i = 0; i < graph.size(); i++)
        graph[i].head = mergeSort(graph[i].head);

    cout << "\nAfter the sort (alphabetically):" << endl;
    printList(graph);

    return 0;
}