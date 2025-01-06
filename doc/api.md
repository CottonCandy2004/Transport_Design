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

## station

### 数据结构
```c
typedef struct {
    double dist[MAX_STATIONS];    // 存储到各站点的距离
    int prev[MAX_STATIONS];       // 存储最短路径的前驱节点
    int visited[MAX_STATIONS];    // 记录节点是否已访问
} PathInfo;
```

### 函数接口

#### find_station_index
在站点数组中查找指定站点的索引。

**语法:**
```c
int find_station_index(vector* stations, const char* station_name)
```

**参数:**
- `stations`: 存储站点的vector指针
- `station_name`: 要查找的站点名称

**返回值:**
- 成功：返回站点在数组中的索引
- 失败：返回-1

#### find_shortest_path
使用Dijkstra算法计算两个站点间的最短路径。

**语法:**
```c
void find_shortest_path(vector* stations, const char* start, const char* end, PathInfo* path_info)
```

**参数:**
- `stations`: 存储站点的vector指针
- `start`: 起始站点名称
- `end`: 终点站点名称
- `path_info`: 用于存储路径信息的结构体指针

**说明:**
- 使用Dijkstra算法计算最短路径
- 结果存储在path_info结构体中
- 如果找不到起点或终点，会打印错误信息

#### traverse_path
遍历并打印（可选）最短路径，返回总距离。

**语法:**
```c
double traverse_path(vector* stations, const PathInfo* path_info, int start_idx, int end_idx, bool printable)
```

**参数:**
- `stations`: 存储站点的vector指针
- `path_info`: 包含路径信息的结构体指针
- `start_idx`: 起始站点索引
- `end_idx`: 终点站点索引
- `printable`:  是否打印路径

**返回值:**
- 成功：返回路径总距离
- 失败：返回-1

**说明:**
- 按顺序打印路径上的所有站点名称
- 如果路径不存在，返回-1

## train

### 函数接口

#### parse_time
将时间字符串解析为time结构体。

**语法:**
```c
void parse_time(const char* time_str, struct time* t)
```

**参数:**
- `time_str`: 时间字符串，格式为分钟数的字符串
- `t`: 指向time结构体的指针

**说明:**
- 输入-1表示无效时间
- 时间将被转换为小时和分钟格式

#### add_station_schedule
向站点添加列车时刻表信息。

**语法:**
```c
void add_station_schedule(struct city_ststion* station, int train_number,
                         struct time* arrival, struct time* departure)
```

**参数:**
- `station`: 指向站点结构的指针
- `train_number`: 列车编号
- `arrival`: 到达时间
- `departure`: 出发时间

**说明:**
- 如果到达或出发时间有效，将添加到对应的时刻表中
- 站点的列车计数会相应增加

#### add_train
添加新的列车信息到列车向量中。

**语法:**
```c
void add_train(vector* trains, const char* name, int number)
```

**参数:**
- `trains`: 存储列车信息的vector指针
- `name`: 列车名称
- `number`: 列车编号

#### find_train
根据列车编号查找列车信息。

**语法:**
```c
struct train* find_train(vector* trains, int number)
```

**参数:**
- `trains`: 存储列车信息的vector指针
- `number`: 要查找的列车编号

**返回值:**
- 成功：返回指向列车结构的指针
- 失败：如果未找到列车，返回NULL
