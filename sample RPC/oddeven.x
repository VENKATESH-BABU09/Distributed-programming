struct rpc{
    int arr[10];
};
program ODD_EVEN_PR{
    version ODD_EVEN_V{
        int oddeven(rpc)=1;
    }=1;
}=0x12345678;