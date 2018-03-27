package ch.epfl.chili.cellulo.cellulorobotpoold;

import android.content.Context;
import android.content.Intent;
import org.qtproject.qt5.android.bindings.QtService;

public class CelluloRobotPoolService extends QtService {

    public static void startCelluloRobotPoolService(Context ctx){
        ctx.startService(new Intent(ctx, ch.epfl.chili.cellulo.cellulorobotpoold.CelluloRobotPoolService.class));
    }

    public static void stopCelluloRobotPoolService(Context ctx){
        ctx.stopService(new Intent(ctx, ch.epfl.chili.cellulo.cellulorobotpoold.CelluloRobotPoolService.class));
    }

}
