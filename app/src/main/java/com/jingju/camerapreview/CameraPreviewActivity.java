package com.jingju.camerapreview;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.jingju.camerapreview.preview.RecordingPreviewScheduler;
import com.jingju.camerapreview.preview.RecordingPreviewView;
import com.jingju.camerapreview.preview.VideoCamera;
import com.jingju.camerapreview.utils.Constant;
import com.jingju.camerapreview.utils.permission.ActivityPermissionDispatcher;
import com.jingju.camerapreview.utils.permission.PermissionCallback;

public class CameraPreviewActivity extends Activity implements PermissionCallback {

	private RelativeLayout recordScreen;
	private RecordingPreviewView surfaceView;
	private VideoCamera videoCamera;
	private RecordingPreviewScheduler previewScheduler;

	private ImageView switchCameraBtn;
	private ActivityPermissionDispatcher dispatcher;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_camera_preview);
		findView();
		bindListener();
		dispatcher = ActivityPermissionDispatcher.getInstance();
		dispatcher.setPermissionCallback(this,this);
		dispatcher.checkedWithCamera(this);
	}

	private void bindListener() {
		switchCameraBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				previewScheduler.switchCameraFacing();
			}
		});
	}

	private void findView() {
		recordScreen = (RelativeLayout) findViewById(R.id.recordscreen);
		switchCameraBtn = (ImageView) findViewById(R.id.img_switch_camera);
		surfaceView = new RecordingPreviewView(this);
		recordScreen.addView(surfaceView, 0);
		surfaceView.getLayoutParams().width = getWindowManager().getDefaultDisplay().getWidth();
		surfaceView.getLayoutParams().height = getWindowManager().getDefaultDisplay().getWidth();
	}

	private void initCameraResource() {
		videoCamera = new VideoCamera(this);
		previewScheduler = new RecordingPreviewScheduler(surfaceView, videoCamera) {
			public void onPermissionDismiss(final String tip) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						Toast.makeText(CameraPreviewActivity.this, tip, Toast.LENGTH_SHORT).show();
					}
				});
			}
		};
	}

	private Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
		}
	};

	@Override
	public void onPermission(int request, int state) {
		switch (request){
			case Constant.PERMISSION_CAMERA_REQUEST_CODE:
				switch (state){
					case SUCCESS:
						dispatcher.checkedWithStorage(this);
						break;
					case DENIED:
					case NEVER_ASK_AGAIN:
						break;
					case EXPLAIN:
						break;
				}

				break;
			case Constant.PERMISSION_STORAGE_REQUEST_CODE:
				if(state==SUCCESS){
					initCameraResource();
				}
				break;
				default:
					break;
		}

	}


	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
		if (dispatcher != null) {
			dispatcher.onRequestPermissionResult(this, requestCode, grantResults);
		}

	}
}
