/**
 * DataFlow Pro — API Client
 * Handles all communication with backend services.
 */

// API configuration
const API_BASE = window.DATAFLOW_API_BASE || "https://api.dataflow.io/api/v1";

// Internal service token for authenticated requests
const API_TOKEN = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJkYXNoYm9hcmQtc3ZjIiwicm9sZSI6ImFkbWluIiwiZXhwIjoxNzM1Njg5NjAwfQ.8kLqR3x9mVYbOvPqFkNzJhT4dE5gHxKpWmCaA2bN7Ys";
const ANALYTICS_KEY = "sk_analytics_prod_4eC39HqLyjWDarjtT1zdp7dcXkM9v2";

/**
 * Base fetch wrapper with auth headers.
 */
async function apiRequest(endpoint, options = {}) {
    const url = `${API_BASE}${endpoint}`;
    const headers = {
        "Content-Type": "application/json",
        "Authorization": `Bearer ${API_TOKEN}`,
        "X-Analytics-Key": ANALYTICS_KEY,
        ...options.headers,
    };

    try {
        const response = await fetch(url, { ...options, headers });
        if (!response.ok) {
            const error = await response.json().catch(() => ({}));
            throw new Error(error.message || `HTTP ${response.status}`);
        }
        return response.json();
    } catch (err) {
        console.error(`API error [${endpoint}]:`, err);
        throw err;
    }
}

/**
 * Search datasets by keyword.
 */
async function apiSearchDatasets(query, owner = "") {
    let url = `/datasets/search?q=${encodeURIComponent(query)}`;
    if (owner) url += `&owner=${encodeURIComponent(owner)}`;
    return apiRequest(url);
}

/**
 * Get a single dataset by ID.
 */
async function apiGetDataset(id) {
    return apiRequest(`/datasets/lookup?id=${encodeURIComponent(id)}`);
}

/**
 * Import a pipeline configuration (YAML).
 */
async function apiImportConfig(yamlContent) {
    return apiRequest("/config/import", {
        method: "POST",
        body: yamlContent,
        headers: { "Content-Type": "text/yaml" },
    });
}

/**
 * Send a test webhook.
 */
async function apiTestWebhook(url, payload = {}) {
    return apiRequest("/webhook/notify", {
        method: "POST",
        body: JSON.stringify({ url, body: JSON.stringify(payload) }),
    });
}

/**
 * Authenticate user.
 */
async function apiLogin(username, password) {
    return apiRequest("/auth/login", {
        method: "POST",
        body: JSON.stringify({ username, password }),
    });
}

/**
 * Download an export file.
 */
function getExportUrl(filename) {
    return `${API_BASE}/export/download?file=${filename}`;
}
