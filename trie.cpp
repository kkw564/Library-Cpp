// For문을 이용한 트라이(재귀 x)
#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
 
using namespace std;
 
const int MAX_NODE = 26;
struct Trie {
    Trie *next[MAX_NODE];
    bool isEnd;
    bool isVisited;
 
    Trie() {
        for (int i = 0; i < MAX_NODE; i++)
        {
            next[i] = nullptr;
            isEnd = isVisited = false;
        }
    }
    ~Trie() {
        for (int i = 0; i < MAX_NODE; i++)
            if (next[i])
                delete next[i];
    }
};
void search(Trie *root) {
    queue<pair<Trie*, string> > q;
    q.push({ root, "" });
 
    while (!q.empty())
    {
        Trie *cur = q.front().first;
        string str = q.front().second;
        q.pop();
 
        for (int i = 0; i < MAX_NODE; i++)
        {
            if (cur->isEnd && !cur->isVisited)
            {
                cout << "찾아낸 값 :: " << str << endl;
                cur->isVisited = true;
            }
            if (cur->next[i])
            {
                if (cur == root)
                {
                    cout << (char)(i + 'A') << endl;
                    Trie *next = cur->next[i];
                    q.push({ next, str + (char)(i + 'A') });
                }
                else
                {
                    cout << str << " 다음 값 :: " << (char)(i + 'A') << endl;
                    Trie *next = cur->next[i];
                    q.push({ next, str + (char)(i + 'A') });
                }
            }
        }
    }
}
 
int main()
{
    Trie *root = new Trie;
 
    for(int i = 0; i < 4; i++)
    {
        char tmp[10];
        scanf("%s", tmp);
 
        Trie *pos = root;
        for (int i = 0; tmp[i]; i++)
        {
            int nowCh = tmp[i] - 'a';
            if (pos->next[nowCh] == nullptr)
                pos->next[nowCh] = new Trie;
 
            pos = pos->next[nowCh];
        }
        pos->isEnd = true;
    }
 
    search(root);
    
    return 0;
}


// 정적 할당을 이용한 트라이
#include <iostream>
 
#define MAX_SIZE 26
 
struct Trie {
  Trie *next[MAX_SIZE];
  bool isEnd;
  int cnt;
};
 
Trie triePool[1000002];
int trieIdx;
 
Trie *root;
 
void init() {
  root = nullptr;
  trieIdx = 0;
}
 
Trie *alloc() {
  for (int i = 0; i < MAX_SIZE; i++)
    triePool[trieIdx].next[i] = nullptr;
  triePool[trieIdx].isEnd = triePool[trieIdx].cnt = 0;
 
  return &triePool[trieIdx++];
}
void insert(int buffer_size, char *buf) {
  if(root == nullptr)
    root = alloc();
 
  Trie *cur = root;
 
  int len = buffer_size;
 
  for (int i = 0; i < len; i++) {
    int ch = buf[i] - 'a';
    if (cur->next[ch] == nullptr)
      cur->next[ch] = alloc();
    
    cur = cur->next[ch];
    cur->cnt++;
  }
  cur->isEnd = true;
}
 
int query(int buffer_size, char *buf) {
  if (root == nullptr)
    return 0;
 
  Trie *cur = root;
  int len = buffer_size;
 
  for (int i = 0; i < len; i++) {
    int ch = buf[i] - 'a';
    if (cur->next[ch] == nullptr)
      return 0;
    cur = cur->next[ch];
  }
 
  return cur->cnt;
}


// 재귀를 이용한 Trie
#include <iostream>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
const int TrieNode = 10; // 트라이 노드마다 포인터 개수
 
struct Trie 
{
    Trie *next[TrieNode]; // 다음 노드를 가리키는 포인터 배열
    bool finish; // 이 노드에서 끝나는 전화번호가 있는가?
    bool nextChild; // 이 노드의 자식이 있는가?
 
    // 생성자
    Trie() 
    {
        fill(next, next + TrieNode, nullptr);
        finish = nextChild = false;
    }
 
    // 소멸자
    ~Trie() 
    {
        for (int i = 0; i < TrieNode; i++)
            if (next[i])
                delete next[i];
    }
 
    // 문자열 key를 현재 노드부터 삽입. 삽입 후 일관성이 있는지를 리턴
    bool insert(const char *key) 
    {
        // 문자열의 끝이라면
        if (*key == '\0') 
        {
            finish = true;
 
            // 문자열이 끝났는데도
            // 자식이 있다면 일관성이 없다.
            if (nextChild)
                return 0;
            else
                return 1;
        }
 
        int nextKey = *key - '0';
 
        // 다음으로 가는 트라이가 없다면
        if (!next[nextKey])
            next[nextKey] = new Trie;
 
        nextChild = true;
 
        // 여기까지 왔다는 의미는 트라이의 자식이 분명히 있다는것.
        // 이때 자식에서 일관성이 없던게 밝혀지거나
        // finish가 true라면 일관성이 없다는 의미.
        bool get = next[nextKey]->insert(key + 1);
 
        return !finish && get;
    }
};
 
int main()
{
    int tc;
    scanf("%d", &tc);
 
    while (tc--)
    {
        int n;
        scanf("%d", &n);
 
        // 트라이의 루트 생성
        Trie *root = new Trie;
 
        bool chk = true;
 
        for (int i = 0; i < n; i++)
        {
            char phone[11];
            scanf("%s", phone);
 
            // 일관성이 없다면
            if (chk && root->insert(phone) == 0)
                chk = false;
        }
 
        if (chk)
            printf("YES\n");
        else
            printf("NO\n");
 
        // 트라이 소멸
        delete root;
    }
 
    return 0;
}