import java.util.*;
public class Final_mitchell
{
    public static void requesting(int[] label,int[] id,int src,int dest)
    {
        int old = label[src];
        label[src] = Math.max(label[src], label[dest])+1;
        System.out.println("p"+id[src]+"->"+id[dest]+"old : "+old+"Updated : "+label[src]);
    }
    public static void transmit(int bnum,int[] label,int[] id,int[][] requests)
    {
        for(int i = bnum-1 ; i>=0 ; i--)
        {
            int from = requests[i][0];
            int to = requests[i][1];
            // int oldId = id[to];
            int oldLabel = id[to];
            id[to] = id[from];
            label[to] = label[from];
            System.out.println("p"+id[from]+"->"+id[to]+" p"+id[to]+" updated !! old value : "+oldLabel+" New value : "+label[to]);
        }
    }
    public static Boolean dfs(ArrayList<ArrayList<Integer>> graph,int node,Boolean[] visited,Boolean[] recursion)
    {
        if(visited[node])
        return false;
        if(recursion[node])
        return true;
        visited[node] = true;
        recursion[node] = true;
        for(int i : graph.get(node) )
        {
            if(dfs(graph,i,visited,recursion))
            return true;
        }
        recursion[node] = false;
        return false;
    }
    public static boolean detectCycle(ArrayList<ArrayList<Integer>> graph,int num)
    {
        Boolean[] visited = new Boolean[num];
        Boolean[] rescursion = new Boolean[num];
        for(int i = 0 ; i<num ; i++)
        {
            if(dfs(graph,i,visited,rescursion))
                return true;
        }
        return false;
    }
    public static void main(String[] args) {
        int num;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of processes : ");
        num = sc.nextInt();
        int[] id = new int[num];
        int[] label = new int[num];
        for(int i = 0 ; i < num ; i++)
        {
            System.out.print("Enter the id and label : ");
            id[i] = sc.nextInt();
            label[i] = sc.nextInt();
        }
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        for(int i = 0 ; i<num ; i++)
        {
            graph.add(new ArrayList<>());
        }
        System.out.print("Enter the number of Block state : ");
        int bnum = sc.nextInt();
        int[][] requests = new int[bnum][2];
        for(int i = 0 ; i < bnum ; i++)
        {
            System.out.print("Enter the src and dest : ");
            int src = sc.nextInt();
            int dest = sc.nextInt();
            for(int j = 0 ; j<num ; j++)
            {
                if(id[j] == src) 
                src = j;
                if(id[j] == dest)
                dest = j;
            }
            requests[i][0] = src;
            requests[i][1] = dest;
            graph.get(src).add(dest);
            requesting(label,id,src,dest);
        }
        transmit(bnum,label,id,requests);
        if(detectCycle(graph,num))
        {
            System.out.println("Cycle detected");
        }
        else
        {
            System.out.println("No cycle detected");
        }
    }
}