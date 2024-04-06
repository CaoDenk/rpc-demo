using Grpc.Core;

namespace rpc_client
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Channel channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);

            var client = new Greeter.GreeterClient(channel);
            String user = "world";
            var msg = new HelloRequest { Name = user };
            msg.Num.Add(5);
            msg.Num.Add(10);
            msg.Num.Add(15);
            msg.Num.Add(18);
            var reply = client.SayHello(msg);

            Console.WriteLine("Greeting: " + reply.Message);

            var  calcclient=new  Calc.CalcClient(channel);

            var result= calcclient.GetSum(new SndNum { Num1 = 5, Num2 = 7 });
            Console.WriteLine($"result{ result}");
            //var res = client.GetSq(new SndNum { Num = 50 });
            //Console.WriteLine("msg"+res.Num);
            channel.ShutdownAsync().Wait();
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
