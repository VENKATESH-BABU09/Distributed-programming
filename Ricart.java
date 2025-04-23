import java.util.*;

class Request {
    int site;
    int timestamp;

    public Request(int site, int timestamp) {
        this.site = site;
        this.timestamp = timestamp;
    }
}

public class Ricart {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the total number of processes (sites): ");
        int totalSites = sc.nextInt();

        System.out.print("Enter the number of sites requesting to enter the critical section: ");
        int requestingSites = sc.nextInt();

        int[] timestamps = new int[totalSites + 1];  // site index from 1
        Request[] requests = new Request[requestingSites];
        ArrayList<Integer>[] deferredReplies = new ArrayList[totalSites + 1];

        // Initialize deferredReplies lists
        for (int i = 1; i <= totalSites; i++) {
            deferredReplies[i] = new ArrayList<>();
        }

        // Read timestamps for all sites
        for (int i = 1; i <= totalSites; i++) {
            System.out.print("Enter the timestamp for Site " + i + ": ");
            timestamps[i] = sc.nextInt();
        }

        // Read which sites want to enter critical section
        for (int i = 0; i < requestingSites; i++) {
            System.out.print("Enter the site number that wants to enter CS: ");
            int site = sc.nextInt();
            requests[i] = new Request(site, timestamps[site]);
        }

        // Handle reply/defer logic
        for (Request r : requests) {
            System.out.println("\n--- Site " + r.site + " wants to enter CS ---");
            for (int j = 1; j <= totalSites; j++) {
                if (j == r.site) continue;

                if (timestamps[j] <= r.timestamp) {
                    System.out.println("Site " + j + " deferred reply to Site " + r.site);
                    deferredReplies[j].add(r.site);
                }else{
                    System.out.println("Site " + j + " replied to Site " + r.site);
                }
            }
        }

        // Sort the requests based on timestamp
        Arrays.sort(requests, Comparator.comparingInt(r -> r.timestamp));

        // Simulate entering critical section
        System.out.println("\n--- Critical Section Access ---");
        for (Request r : requests) {
            System.out.println("Site " + r.site + " entered CS");

            for (int deferredSite : deferredReplies[r.site]) {
                System.out.println("Site " + r.site + " replies to deferred Site " + deferredSite);
            }

            deferredReplies[r.site].clear(); // After replying
        }

        sc.close();
    }
}
