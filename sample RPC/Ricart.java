import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
import java.util.*;

class Request{
    int pid;
    int timestamp;

    public Request(int pid,int timestamp){
        this.pid=pid;
        this.timestamp=timestamp;
    }
}

public class Ricart{

    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("enter the number of processes:");
        int numproc=sc.nextInt();
        int[] timestamp=new int[numproc+1];
        System.out.println("Enter the number of sites want to enter cs:");
        int requestproc=sc.nextInt();
        Request[] requests=new Request[requestproc];
        ArrayList<Integer>[] deffered=new ArrayList[numproc+1];

        for(int i=1;i<=numproc;i++){
            System.out.println("enter the timestamp of process "+i+" : ");
            timestamp[i]=sc.nextInt();
            deffered[i]=new ArrayList<>();
        }

        for(int i=0;i<requestproc;i++){
            System.out.println("enter the site that want to enter CS: ");
            int site=sc.nextInt();
            requests[i]=new Request(site, timestamp[site]);
        }

        for(Request r:requests){
            System.out.println("Site "+r.pid+" wants to enter CS");
            for(int j=1;j<=numproc;j++){
                if(j!=r.pid){
                    if(timestamp[j]>timestamp[r.pid]){
                        System.out.println("site "+j+" replied to site "+r.pid);
                    }
                    else{
                        System.out.println("site "+j+" deffered to site "+r.pid);
                        deffered[j].add(r.pid);
                    }
                }
            }
        }

        Arrays.sort(requests,Comparator.comparingInt(r->r.timestamp));


        System.out.println("------critical section area--------");

        for(Request r:requests){
            System.out.println("site "+r.pid+" entered cs");
            if(!deffered[r.pid].isEmpty()){
                for(int p:deffered[r.pid]){
                    System.out.println("site "+r.pid+" replies to "+p);
                }
                deffered[r.pid].clear();

            }

        }
        



    }
}