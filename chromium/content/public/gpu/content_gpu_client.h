// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_GPU_CONTENT_GPU_CLIENT_H_
#define CONTENT_PUBLIC_GPU_CONTENT_GPU_CLIENT_H_

#include "base/metrics/field_trial.h"
#include "base/task/single_thread_task_runner.h"
#include "content/common/content_export.h"
#include "content/public/common/content_client.h"
#include "mojo/public/cpp/bindings/binder_map.h"

namespace gpu {
struct GpuPreferences;
class GpuDriverBugWorkarounds;
class SharedImageManager;
class SyncPointManager;
}

namespace gl {
class GLShareGroup;
}

namespace viz {
class VizCompositorThreadRunner;
}

namespace content {

// Embedder API for participating in gpu logic.
class CONTENT_EXPORT ContentGpuClient {
 public:
  virtual ~ContentGpuClient() {}

  // Called during initialization once the GpuService has been initialized.
  virtual void GpuServiceInitialized() {}

  // Registers Mojo interface binders that can handle interface requests from
  // the browser. Binders registered here will never run until the GPU process
  // has received a |CreateGpuService()| call from the browser.
  virtual void ExposeInterfacesToBrowser(
      const gpu::GpuPreferences& gpu_preferences,
      const gpu::GpuDriverBugWorkarounds& gpu_workarounds,
      mojo::BinderMap* binders) {}

  // Called right after the IO/compositor thread is created.
  virtual void PostIOThreadCreated(
      base::SingleThreadTaskRunner* io_task_runner) {}
  virtual void PostCompositorThreadCreated(
      base::SingleThreadTaskRunner* task_runner) {}

  // Allows client to supply these object instances instead of having content
  // internally create one.
  virtual gpu::SyncPointManager* GetSyncPointManager();
  virtual gpu::SharedImageManager* GetSharedImageManager();
  virtual viz::VizCompositorThreadRunner* GetVizCompositorThreadRunner();
  // Allow an embedder to provide a share group reimplementation to connect renderer
  // GL contexts with the root compositor.
  virtual gl::GLShareGroup* GetInProcessGpuShareGroup();
};

}  // namespace content

#endif  // CONTENT_PUBLIC_GPU_CONTENT_GPU_CLIENT_H_
