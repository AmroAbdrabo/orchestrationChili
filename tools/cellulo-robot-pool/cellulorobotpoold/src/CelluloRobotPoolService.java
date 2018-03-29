package ch.epfl.chili.cellulo.cellulorobotpoold;

import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import org.qtproject.qt5.android.bindings.QtService;

public class CelluloRobotPoolService extends QtService {

    public static void startCelluloRobotPoolService(Context ctx){
        ctx.startService(new Intent(ctx, ch.epfl.chili.cellulo.cellulorobotpoold.CelluloRobotPoolService.class));
    }

    public static void stopCelluloRobotPoolService(Context ctx){
        ctx.stopService(new Intent(ctx, ch.epfl.chili.cellulo.cellulorobotpoold.CelluloRobotPoolService.class));
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);
        return ret;
    }

    @Override
    public IBinder onBind(Intent intent) {
        IBinder ret = super.onBind(intent);
        return ret;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        boolean ret = super.onUnbind(intent);
        return ret;
    }

    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }
}
