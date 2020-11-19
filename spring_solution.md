# 白银之春 Solution

## Fun Facts

- [森罗结界 - 东方妖妖梦](https://thwiki.cc/%E6%A3%AE%E7%BD%97%E7%BB%93%E7%95%8C)
- [人妖槽 - 东方永夜抄](https://thwiki.cc/%E6%B8%B8%E6%88%8F%E6%94%BB%E7%95%A5/%E4%B8%9C%E6%96%B9%E6%B0%B8%E5%A4%9C%E6%8A%84/%E7%B3%BB%E7%BB%9F#%E5%9F%BA%E6%9C%AC%E4%BA%8B%E9%A1%B9)
- 题目名neta的是妖妖梦一面的卷首语。

## Solution

### 无环图

DAG上dp就好了。设状态 $f[u][0/1]$ 为到达点 $u$ 时状态为 $0/1$ 可收集到的最大春度，若 $f[u][t]$ 可达，有
$$
f[u][t] = t \times \mathrm{val}[u] + \max_{(v,w) \in \mathrm{pre}_u} f[v][t \otimes w]
$$
其中 $\mathrm{val}[u]$ 是点 $u$ 的权值， $(v,w) \in \mathrm{pre}_u$ 表示 $u$ 在DAG上的前驱边， $\otimes$ 代表异或。

答案即 $\max_{u \in G} \max(f[u][0],f[u][1])$ 。

### 普通图

普通图有环，环上的状态转移方程相互依赖，无法dp。

根据部分分的提示，考虑缩点。

不妨先看所有强连通分量都只是简单环的情况。

#### 环套DAG

为了方便描述，我们定义如下两种描述：

- 奇环：环上所有边权异或和为 $1$ 的环。
- 偶环：环上所有边权异或和为 $0$ 的环。

容易发现奇环上可以通过绕一圈的方式回到原点，使状态发生改变。也就是说，不论从进出位置和初始状态如何，一个奇环总可以输出任意的 $0$ 或 $1$ 。而如果在奇环上绕两圈，就可以取得环上所有点的春度。所以直接缩点处理即可。

那么偶环如何处理呢？

首先，若进入偶环的的位置（入点）确定，无论怎样在偶环上绕圈，到达环上某点（出点）时的状态总是唯一确定的。

进一步的，偶环上的点可根据到达该点时的状态被分为两组。组与组之间在环上交错排列，所有边权为 $1$ 的边都是都是一个间隔。若入点和出点在同一组内，则状态不会发生变化；反之则状态改变。这启发我们将偶环缩成两个点来处理，每一个点代表一个组。

考虑春度的获取。如果进入时状态为 $0$ ，那么和入点在同一组内的点上的春度都无法取得（因为经过该点时状态始终为 $0$ ），而在不同组的点上的春度能够取得（因为经过该点时状态始终为 $1$ ）；反之，若进入时状态为 $1$ ，那么和入点在同一组的点上的春度可以取得，在不同组的不能取得。

缩点后做一些讨论就可以了。

#### 强连通分量

在环上我们已经发现——奇环可以特殊处理，而偶环内的点可以被分成两组。强连通分量是否有与其相似的性质呢？

##### 奇强连通分量

强连通分量无非是许多个环叠起来的连通块。如果一个强连通分量包含一个或多个奇环（称之为“奇强连通分量”），那么该强连通分量同样有奇环的性质——每个点都可以通过在奇环上绕圈获得 $0/1$ 两种状态，块上所有点的春度都能取得。

实测发现随机图中出现偶强连通分量的概率极小，因此只处理奇强连通分量的算法可以通过随机图数据。

##### 偶强连通分量

剩下的问题已经很明确了——处理所含环全都是偶环的强连通分量（称之为“偶强连通分量”）。

可以发现这一结论：无论如何在偶强连通分量中游走，只要入点和进入时的状态确定，那么每个点的状态就唯一确定。于是偶强连通分量中的点也可以被分成两组，好比环套DAG中的偶环。

易用反证法证明该性质：在一偶强连通分量中，假设点 $u$ 到点 $v$ 同时存在偶路径 $P$ 和奇路径 $Q$ 。那么奇路径 $Q$ 必然与某条从 $v$ 到 $u$ 的奇路径 $R$ 共同组成了一个偶环（偶强连通分量中只有偶环且各点强连通）。则偶路径 $P$ 和奇路径 $R$ 构成奇环，与假设矛盾，故性质成立。

春度的获取也与偶环相同。

判断一个强连通分量是奇是偶，只需二分图染色，取环上任意一个点作为起点DFS，如果能以不同的状态到达某点，那该分量就是奇的，反之则是偶的。正确性比较显然，证明在此略去。

### 实现

实现细节较多，建议缩点后重新建图。

可以用4个节点分别代理两个分组各自的入边和出边，算出到达该组状态为 $0/1$ 时连通块内两个组的点权对答案的贡献。为了方便，实现时可以以边数x2的代价把节点数压缩到2个。

## Omake

第一次出题，有纰漏请多多包涵。

快要交题时才发现一年前写的std出锅了，匆匆忙忙的重写了一个，不知道有没有新造出什么bug。数据也造得比较匆忙，如果爆炸了请随便辱骂出题人或者[去他博客上](https://www.cnblogs.com/sun123zxy/p/14019963.html)告诉他（

可以说这道题把二分图拓展到了强连通有向图上，不知道有没有什么更有趣的性质可以发掘。

后来做到几道性质相似的题目，这里列出来供参考： ~~垃圾撞题出题人~~

+ [CF1444C - Codeforces Round #680 - Team-Building](https://codeforces.com/contest/1444/problem/C) ([official solution](https://codeforces.com/blog/entry/84248))
+  [LOJ508 - LibreOJ NOI Round #1 - 失控的未来交通工具](https://loj.ac/problem/508) ([official solution](https://loj.ac/article/87))

思考背景怎样与题目契合也是个挺有趣的过程。

题面、题解、标程和数据生成器都挂在 [git@github.com:sun123zxy/spring.git](https://github.com/sun123zxy/spring) 上，可自行获取。

感谢听我乱扯idea的 TbYangZ 和 Waper ，以及尝试叉掉std的两位勇士 p9t6g 和 changruinian2020 。 ~~虽然都失败了~~ 

就这些吧。



<p align="right">——sun123zxy</p>

<p align="right">Oct. 2019 初稿完成 </p>

<p align="right">Nov. 2020 最后更新</p>



**Next Phantasm...**