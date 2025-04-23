import java.util.*;
public class Suzuki_Kasami {
    static int numprocs;
    static int tokenholder=0;
    static int[] LN;
    static int[] RN;
    static List<Integer> tokenQueue=new ArrayList<>();
    static Map<Integer,Integer> executionTick=new HashMap<>();


    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("enter the number of processes");
        numprocs=sc.nextInt();
        RN=new int[numprocs];
        LN=new int[numprocs];
        for(int i=0;i<numprocs;i++){
            LN[i]=0;
            RN[i]=0;
        }
        for(int i=0;i<numprocs;i++){
            System.out.println("enter the execution tick for process "+i+" : ");
            executionTick.put(i,sc.nextInt());
        }
        System.out.println("token is initally with process 0..... ");

        printState();
        sc.nextLine();

        while(true){
            System.out.println("enter the sites that want to enter CS: ");
            String line=sc.nextLine();
            if(line.equals("-1")){
                System.out.println("going to exit ....");
                break;
            }
            try{

                
                String[] processIDS=line.trim().split("\\s+");
                List<Integer> requests=new ArrayList<>();
                for(String pids:processIDS){
                    requests.add(Integer.parseInt(pids));
                }

                handleRequests(requests);
            }catch(NumberFormatException e){
                System.out.println("invalid input");
            }
        }
       


    }

    public static void handleRequests(List<Integer> processes){
        for(int pid:processes){
            RN[pid]++;
            System.out.println("site "+pid+" requests CS (request  number):"+RN[pid]);
            if(!tokenQueue.contains(pid)){
                tokenQueue.add(pid);
            }
        }

        printState();

        while(!tokenQueue.isEmpty()){
            int nextproc=tokenQueue.get(0);
            if(tokenholder==nextproc){
                executeCS(nextproc);
            }else{
                System.out.println("checking the current token holder "+tokenholder+" want to pass token to "+nextproc);
                if(RN[nextproc]>LN[nextproc]){
                    passToken(nextproc);
                }else{
                    System.out.println("Process "+nextproc+" no need token token anymore so removing from queue");
                    tokenQueue.remove(0);
                }
            }
        }




    }

    public static void passToken(int process){
        System.out.println("process "+tokenholder+"pass the token to "+process);
        tokenholder=process;
        tokenQueue.remove(Integer.valueOf(process));
        printState();
        executeCS(process);
    }

    public static void executeCS(int process){
        System.out.println("the process "+process+" is going to execute for "+executionTick.get(process)+"ticks ");
        System.out.println(">>>process "+process+"entered CS");
        for(int i=1;i<=executionTick.get(process);i++){
            System.out.println("TICK "+i+"....");
        }
        System.out.println(">>>process "+process+" exited CS" );
        LN[process]=RN[process];
        printState();
        checkWaitingProc();
    }

    public static void checkWaitingProc(){
        while(!tokenQueue.isEmpty()){
            int nextprocess=tokenQueue.get(0);
            if(RN[nextprocess]>LN[nextprocess]){
                passToken(nextprocess);
                return;
            }else{
                System.out.println("the process "+nextprocess+" waiting in the queue but does notr need anymore");
                tokenQueue.remove(0);
            }
        }
        System.out.println("no more processes waiting for toekn");

    }

    public static void printState(){
        System.out.println("------current state-------");
        System.out.println("RN :"+Arrays.toString(RN));
        System.out.println("LN:"+Arrays.toString(LN));
        System.out.println("TokenQueue: "+tokenQueue);
        System.out.println("TokenHolder :"+tokenholder);

    }
    
}
