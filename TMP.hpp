public:
void d()
{
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
	display(this->_root, 1);
	printf("\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}
void display(NodePtr ptr, int level)
{
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");


		for (i = 0; i < level && ptr != this->_root; i++)
		{
			if (i == level - 1)
				printf("           ");

			else if (i == level - 2)
				printf("            ┃");
			else
			{

        		printf("            ┃");
			}
        }
		if (ptr == this->_root)
			printf("           ");
		printf("[\033[32m%hhd\033[0m]\n", ptr->bf );

		if (ptr == this->_root)
            printf("Root -> ");

		for (i = 0; i < level && ptr != this->_root; i++)
		{

			if (i == level -1)
			{
				if (ptr != this->_root && is_left_child(ptr))
				{
					printf("\b┗━━━━━━━━━━━");
					break;
				}
				else if (ptr != this->_root && is_right_child(ptr))
				{

					printf("\b┏━━━━━━━━━━━");
					break;
				}
				else
				{
					printf("           ");
				}
			}

			else
        		printf("            ┃");

        }
        printf("\033[92;35m%d\033[0m\n", ptr->val.first);


		for (i = 0; i < level && ptr != this->_root; i++)
		{
			if (i == level - 1)
				printf("           ");
			else if (i == level - 2)
				printf("            ┃");
			else
        		printf("            ┃");
        }
		if (ptr == this->_root)
			printf("           ");
		printf("[\033[92;34m%d\033[0m]",(ptr->parent ? ptr->parent->val.first: 0) );

        display(ptr->left, level + 1);
    }
}
