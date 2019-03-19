#include <stdio.h>
#define Q_MAX 10
#define Q_EMPTY -1000

int que[Q_MAX + 1];
int head = 0;
int tail = 0;

int enque(int key) {
	if(tail > 0) {
		if(head == tail - 1)
			return 0;
		que[tail--] = key;
		return 1;
	}
	else {
		if(head == Q_MAX)
			return 0;
		que[0] = key;
		tail = Q_MAX;
		return 1;
	}
}

int deque() {
	if(head == tail)
		return Q_EMPTY;
	else {
		if(head > 0)
			return que[head--];
		else {
			head = Q_MAX;
			return que[0];
		}
	}
}

int main() {
	int op = 1;
	int key;
	int res;
	while(op) {
		if(op == 1) {
			scanf("%d", &key);
			res = enque(key);
			if(res)
				puts("queued.\n");
			else
				puts("full.\n");
		}
		else if(op == 2) {
			res = deque();
			if(res != Q_EMPTY)
				printf("dequeued %d\n", res);
			else
				puts("empty.\n");
		}
		else if(op == 3) {
			puts("---");
			for(int i = 0; i <= Q_MAX; i++) {
				if(head > tail) {
					if(i <= tail || i > head)
						printf("%c ", '-');
					else
						printf("%d ", que[i]);
				}
				else {
					if(i > head && i <= tail)
						printf("%c ", '-');
					else
						printf("%d ", que[i]);
				}
			}
		}
		scanf("%d", &op);
	}

	return 0;
}