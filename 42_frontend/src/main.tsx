// import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import Router from "./routes/index.tsx";
import {
  QueryClient,
  QueryClientProvider,
  // useQuery,
} from "@tanstack/react-query";

const queryClient = new QueryClient();

createRoot(document.getElementById("root")!).render(
  // <StrictMode>
  <QueryClientProvider client={queryClient}>
    <Router />
  </QueryClientProvider>
  // </StrictMode>
);
