void d()
{
	display(this->_root, 1);
}
void display(NodePtr ptr, int level)
{
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == this->_root)
            printf("Root -> ");
        for (i = 0; i < level && ptr != this->_root; i++) {
            printf("        ");
        }
        printf("\033[92;35m%d\033[0m [\033[32m%zu\033[0m]", ptr->val.first, ptr->height);
        display(ptr->left, level + 1);
    }
}
