/*review the preTraverse,midTraverse,postTraverse
 *review known preTraverse,midTraverse ,get post-
 * -traverse,using recursion.
*/

#include <iostream>
#include <string>
using namespace std;
class Node{
public:
    Node():left(NULL),right(NULL){}
    char value;
    Node* left;
    Node* right;
};
class Tree{
public:
    Tree():Head(NULL){}
    ~Tree(){}
    void Insert(Node* node);
    Node* getHead();
    void setHead(Node* ptr);
private:
    Node* Head;
};
void Tree::Insert(Node* node) {
    if(Head){
        auto ptr=Head;
        while(1){
            if(node->value<=ptr->value){
                if(ptr->left){
                    ptr=ptr->left;
                }
                else{
                    ptr->left=node;
                    break;
                }
            }
            else{
                if(ptr->right){
                    ptr=ptr->right;
                }
                else{
                    ptr->right=node;
                    break;
                }
            }
        }
    }
    else{
        Head=node;
    }
}
Node* Tree::getHead() {
    return Head;
}
void Tree::setHead(Node* ptr){
    Head=ptr;
}
Tree tree;
void midTraverse(Node* node){
    if(node){
        midTraverse(node->left);
        cout<<(node->value)<<' ';
        midTraverse(node->right);
    }
}
void preTraverse(Node* node){
    if(node){
        cout<<(node->value)<<' ';
        preTraverse(node->left);
        preTraverse(node->right);
    }
}

void postTraverse(Node* node){
    if(node){
        postTraverse(node->left);
        postTraverse(node->right);
        cout<<node->value<<' ';
    }
}
Node* buildTree(char* preBegin,char* midBegin,int length){
    auto ptr=new Node;
    if(length){
        ptr->value=preBegin[0];
        auto res=strchr(midBegin,preBegin[0]);
        int count=res-midBegin;
        ptr->left=buildTree(preBegin+1,midBegin,count);
        ptr->right=buildTree(preBegin+count+1,midBegin+count+1,length-count-1);
        return ptr;
    }
    else{
        return NULL;
    }
}
int main(void){
    int num=1;
    /*while(1){
        cin>>num;
        if(num==-1){
            break;
        }
        auto ptr=new Node;
        ptr->value=num;
        tree.Insert(ptr);
    }
    auto head=tree.getHead();
    preTraverse(head);
    cout<<endl;
    midTraverse(head);
    cout<<endl;
    postTraverse(head);*/
    string pre,mid;
    cin>>pre>>mid;
    tree.setHead(buildTree(&pre[0],&mid[0],pre.size()));
    auto head=tree.getHead();
    postTraverse(head);
}