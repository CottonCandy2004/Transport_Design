# API 文档

## vector

### 对象结构以及方法
```c
typedef struct vector{
    void* data;
    int size;
    int capacity;
    size_t element_size;

    void (*free)(struct vector* v);
    void (*push_back)(struct vector* v, void* element);
    void (*pop_back)(struct vector* v);
    int (*get_size)(struct vector* v);
    void* (*get)(struct vector* v, int index);
} vector;
```

### 函数接口

#### vector_init
初始化vector结构。

**语法:**
```c
void vector_init(struct vector* v, size_t element_size)
```

**参数:**
- `v`: 指向vector结构的指针
- `element_size`: 存储元素的字节大小

**说明:**
- 初始化一个新的vector，分配初始容量为 VECTOR_INIT_CAPACITY 的内存空间
- 设置初始size为0，capacity为VECTOR_INIT_CAPACITY
- 初始化所有方法链接

> 请务必确保您使用新创建的结构体前已初始化
> 默认情况下，VECTOR_INIT_CAPACITY为4

#### vector_free
释放vector占用的内存。

**语法:**
```c
void vector_free(struct vector* v)
```

**参数:**
- `v`: 指向vector结构的指针

#### vector_push_back
在vector末尾添加新元素。

**语法:**
```c
void vector_push_back(struct vector* v, void* element)
```

**参数:**
- `v`: 指向vector结构的指针
- `element`: 指向要添加元素的指针

**说明:**
- 如果容量不足，会自动扩容为原来的2倍
- 使用memcpy复制元素数据

#### vector_pop_back
移除vector末尾的元素。

**语法:**
```c
void vector_pop_back(struct vector* v)
```

**参数:**
- `v`: 指向vector结构的指针

#### vector_size
获取vector中的元素数量。

**语法:**
```c
int vector_size(struct vector* v)
```

**参数:**
- `v`: 指向vector结构的指针

**返回值:**
- 返回vector中当前的元素数量

#### vector_get
获取指定索引位置的元素。

**语法:**
```c
void* vector_get(struct vector* v, int index)
```

**参数:**
- `v`: 指向vector结构的指针
- `index`: 要获取元素的索引位置

**返回值:**
- 成功：返回指向元素的指针
- 失败：如果索引越界，返回NULL

**注意:**
- 索引范围必须在0到size-1之间
