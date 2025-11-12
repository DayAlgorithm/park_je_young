use std::io::{self, Read};

fn main() {

    let mut input = String::new();

    io::stdin().read_to_string(&mut input).unwrap();

    let mut it = input.split_whitespace().map(|s| s.parse::<usize>().unwrap());

    let t = it.next().unwrap();

    let mut out = String::new();

    for _case in 0..t {

        let n = it.next().unwrap();

        // adjacant
        let mut adj = vec![Vec::<usize>::new(); n + 1];
        let mut indeg = vec![0usize; n + 1];
        let mut parent0 = vec![0usize; n + 1];

        for _ in 0..(n - 1) {
            let a = it.next().unwrap(); 
            // parent
            let b = it.next().unwrap(); 
            // child
            adj[a].push(b);
            parent0[b] = a;
            indeg[b] += 1;
        }

        // 루트 찾기
        let mut root = 1usize;
        for v in 1..=n {
            if indeg[v] == 0 {
                root = v;
                break;
            }
        }

        // 깊이 계산과 parent[0] 확정 
        let mut depth = vec![0usize; n + 1];
        let mut stack = Vec::with_capacity(n);
        stack.push(root);
        parent0[root] = 0; 
        // 루트의 부모는 0(가상의 노드)

        // 트리는 방향(parent to child)이므로 topological searching.
        while let Some(v) = stack.pop() {
            for &to in &adj[v] {
                depth[to] = depth[v] + 1;
                stack.push(to);
            }
        }

        // binary lifting
        let mut log = 1usize;
        while (1usize << log) <= n {
            log += 1;
        }
        let mut parent = vec![vec![0usize; n + 1]; log];
        parent[0] = parent0;

        for k in 1..log {
            for v in 1..=n {
                let mid = parent[k - 1][v];
                parent[k][v] = if mid == 0 { 0 } else { parent[k - 1][mid] };
            }
        }

        // 질의(u, v) 읽기
        let mut u = it.next().unwrap();
        let mut v = it.next().unwrap();

        // LCA u to v
        // depth checking line.
        if depth[u] < depth[v] {
            std::mem::swap(&mut u, &mut v);
        }

        let mut diff = depth[u] - depth[v];
        let mut bit = 0usize;
        
        while diff > 0 {
            
            if diff & 1 == 1 {
                u = parent[bit][u];
            }
            
            diff >>= 1;
            
            bit += 1;
        
        }

        // same
        if u == v {
            
            out.push_str(&format!("{}\n", u));
            
            continue;
        
        }

        // goto : up and jump
        for k in (0..log).rev() {
            if parent[k][u] != parent[k][v] {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        // origin + 1 == sameParent
        out.push_str(&format!("{}\n", parent[0][u]));
    }

    print!("{out}");
}
