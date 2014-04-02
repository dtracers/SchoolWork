import java.util.Iterator;
import java.util.List;

import com.brackeen.javagamebook.game.GameObject;
import com.brackeen.javagamebook.math3D.PolygonGroup;
import com.brackeen.javagamebook.path.PathBot;
import com.brackeen.javagamebook.scripting.GameTaskManager;
import com.brackeen.javagamebook.scripting.ScriptManager;


public class CarTest extends EventTest
{
	public static void main(String[] args)
	{
        new CarTest(args, "images/myLevel.map").run();
    }
	public CarTest(String[] args, String defaultMap)
	{
		super(args, defaultMap);
		// TODO Auto-generated constructor stub
	}
	public void init() {
        super.init();
        gameTaskManager = new GameTaskManager();
        scriptManager = new ScriptManager();
        scriptManager.setupLevel(gameObjectManager,
            gameTaskManager, new String[] {
            "scripts/Mine.bsh", "scripts/myLevel.bsh" });
    }
	protected void createGameObjects(List mapObjects)
	{
        Iterator i = mapObjects.iterator();
        while (i.hasNext()) {
            Object object = i.next();
            if (object instanceof PolygonGroup) {
                PolygonGroup group = (PolygonGroup)object;
                if ("toy2".equals(group.getName())) {
                    gameObjectManager.add(new PathBot(group));
                }
                else {
                    gameObjectManager.add(new GameObject(group));
                }
            }
            else if (object instanceof GameObject)
            {
                gameObjectManager.add((GameObject)object);
            }

        }
    }
	public void updateWorld(long elapsedTime)
	{
        super.updateWorld(elapsedTime);
        gameTaskManager.update(elapsedTime);

    }
}
