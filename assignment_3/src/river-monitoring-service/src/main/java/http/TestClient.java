package http;
import java.util.Random;
import io.vertx.core.AbstractVerticle;

public class TestClient extends AbstractVerticle {
	
	public static void main(String[] args) throws Exception {		

		HTTPcommunicator communicator = new HTTPcommunicator();
		Random random = new Random();
		
		for (int i = 0; i < 20; i++) {
			communicator.write(20 + Math.random()*5, random.nextInt(6), "ok");
			Thread.sleep(10000);
			if(communicator.check().isEmpty()) {
				System.out.println("prova lettura");
			}
		}
	}
	
}
